using Godot;
using System;

public partial class Card : Sprite3D
{
	private Vector3 originalScale;
	private Vector3 originalPosition;
	private Camera3D camera3d;
	private bool isHovered = false;
	private bool tweenIsDone = false;
	private bool onBoard = false;
	private const float RAY_LENGTH = 10.0f;
	private Tween tween;
	private Area3D collisionArea;
	private StaticBody3D inkwell;

	private bool isDragging = false;
	private const float RELEASE_THRESHOLD_HEIGHT = -1.5f;

	public override void _Ready()
	{
		originalScale = Scale;
		originalPosition = Position;
		camera3d = GetTree().Root.GetNode<Camera3D>("Game/Camera3D");
		Init();
		
		//LORE_Card test;
	}

	private void Init()
	{
		collisionArea = GetNode<Area3D>("Area3D");
		inkwell = GetNode<StaticBody3D>("/root/Game/Inkwell");
	}

	public override void _Input(InputEvent @event)
	{
		if (@event.IsActionPressed("Left Click"))
		{
			if (IsMouseOver(collisionArea))
			{
				isDragging = true;
				// A Tween will override the position, stop tweening so that the 
				// position of this Card can be set.
				if (tween != null)
				{
					tween.Kill();
				}
			}
		}
		else if (@event.IsActionReleased("Left Click"))
		{
			if (isDragging)
			{
				isDragging = false;

				// Check collision between the card and various areas like board, inkwell, etc.
				if (IsMouseOver(inkwell, collisionArea))
				{
					tween = CreateTween().SetTrans(Tween.TransitionType.Linear).SetEase(Tween.EaseType.In);
					tween.TweenProperty(this, "rotation_degrees", new Vector3(90, 0, 0), 0.5f);
					tween.Parallel();
					tween.TweenProperty(this, "scale", new Vector3(0, 0, 0), 0.5f);
					tween.TweenCallback(Callable.From(QueueFree));
					onBoard = true;
				}
				// If card is raised high enough, play it if possible.
				else if (Position.Z < RELEASE_THRESHOLD_HEIGHT && Owner.CanPlay(this))
				{
					// Game can potentially hang on to objects.
					// Game.PlayCard(this);
					// Maybe it has a table of csharp objects to c objects.
					Owner.PlayCard(this);

					// Need to be able to access properties
					this.Cost;
					// this.Owner; ?
					// get -> Lore.Card(this).Cost ?

					// Reset position after playing the card
					tween = CreateTween().SetTrans(Tween.TransitionType.Expo).SetEase(Tween.EaseType.Out);
					tween.TweenProperty(this, "position", new Vector3(originalPosition.X, -0.25f, -1.5f), 0.5f);

					RotationDegrees = new Vector3(-90, 0, 0);
					onBoard = true;
				}
				else
				{
					TweenBack(1.0f);
				}
			}
		}
	}

	public override void _PhysicsProcess(double delta)
	{
		// Handle dragging
		if (isDragging)
		{
			// Snap the card to the mouse's position.
			Vector3 newPosition = camera3d.ProjectPosition(GetViewport().GetMousePosition(), camera3d.GlobalTransform.Origin.Z + 1.25f);
			GlobalPosition = newPosition;
			return;
		}

		if (onBoard)
		{
			return;
		}

		// Check if the mouse is over the card
		if (IsMouseOver(collisionArea))
		{
			// If the card is not already hovered, start the animation
			if (!isHovered)
			{
				isHovered = true;
				tween = CreateTween().SetTrans(Tween.TransitionType.Expo).SetEase(Tween.EaseType.Out);
				tween.TweenProperty(this, "position", originalPosition - new Vector3(0, -0.5f, 0.5f), 0.5f);
			}
		}
		else
		{
			// If the card is hovered but the mouse is not over it anymore, reverse the animation
			if (isHovered)
			{
				isHovered = false;
				TweenBack(0.5f);
			}
		}
	}

	private void TweenBack(float duration)
	{
		// Tween this card back to its original position.
		tween = CreateTween().SetTrans(Tween.TransitionType.Expo).SetEase(Tween.EaseType.Out);
		tween.TweenProperty(this, "position", originalPosition, duration);
	}

	// Check if the mouse is over a given collision object (shape3d or area3d).
	private bool IsMouseOver(CollisionObject3D collisionObject3D, params CollisionObject3D[] excludes)
	{
		Vector2 screenPoint = GetViewport().GetMousePosition();
		Vector3 from = camera3d.ProjectRayOrigin(screenPoint);
		Vector3 to = from + camera3d.ProjectRayNormal(screenPoint) * RAY_LENGTH;
		var query = PhysicsRayQueryParameters3D.Create(from, to);
		query.CollideWithAreas = true;
		query.CollideWithBodies = true;
		foreach (var exclude in excludes)
		{
			query.Exclude.Add(exclude.GetRid());
		}
		var result = GetWorld3D().DirectSpaceState.IntersectRay(query);
		return result.ContainsKey("rid") && (Rid)result["rid"] == collisionObject3D.GetRid();
	}
}
