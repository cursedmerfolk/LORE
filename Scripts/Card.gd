extends Sprite3D

var GameState = load("res://RulesEngine/main.cs")

var original_scale: Vector3
var original_position: Vector3
var camera3d: Camera3D
var is_hovered: bool = false
var tween_is_done: bool = false
var on_board: bool = false
var RAY_LENGTH: float = 10.0
var tween: Tween
var collision_area: Area3D
var inkwell: StaticBody3D
var game_state

var is_dragging: bool = false
var RELEASE_THRESHOLD_HEIGHT: float = -1.5

func _ready():
	original_scale = scale
	original_position = position
	camera3d = get_tree().get_root().get_node("Game/Camera3D")
	init()

func init():
	collision_area = get_node("Area3D")
	inkwell = get_node("/root/Game/Inkwell")

	# Api for keeping track of Game state.
	game_state = GameState.new("player1", "player2")

func _input(event):
	if event.is_action_pressed("Left Click"):
		if is_mouse_over(collision_area):
			is_dragging = true
			# A Tween will override the position, stop tweening so that the 
			# position of this Card can be set.
			if tween:
				tween.kill()
	elif event.is_action_released("Left Click"):
		if is_dragging:
			is_dragging = false

			# Check collision between the card and various areas like board, inkwell, etc.
			if is_mouse_over(inkwell, [collision_area]):

				game_state.InkCard("player1", 0)

				tween = create_tween().set_trans(Tween.TRANS_LINEAR).set_ease(Tween.EASE_IN)
				tween.tween_property(self, 'rotation_degrees', Vector3(90, 0, 0), .5)
				tween.parallel()
				tween.tween_property(self, 'scale', Vector3(0, 0, 0), .5)
				tween.tween_callback(queue_free)
				on_board = true

			# If card is raised high enough, play it if possible.
			elif position.z < RELEASE_THRESHOLD_HEIGHT:

				game_state.PlayCard("player1", 0)

				# Reset position after playing the card
				tween = create_tween().set_trans(Tween.TRANS_EXPO).set_ease(Tween.EASE_OUT)
				tween.tween_property(self, 'position', Vector3(original_position.x, -0.25, -1.5), 0.5)
				
				rotation_degrees = Vector3(-90, 0, 0)
				on_board = true
			else:
				tween_back(1.0)

func _physics_process(_delta):

	# Handle dragging
	if is_dragging:
		# Snap the card to the mouse's position.
		var new_position: Vector3 = camera3d.project_position(get_viewport().get_mouse_position(), camera3d.global_transform.origin.z + 1.25)
		global_position = new_position
		return

	if on_board:
		return

	# Check if the mouse is over the card
	if is_mouse_over(collision_area):
		# If the card is not already hovered, start the animation
		if not is_hovered:
			is_hovered = true
			tween = create_tween().set_trans(Tween.TRANS_EXPO).set_ease(Tween.EASE_OUT)
			tween.tween_property(self, 'position', original_position - Vector3(0, -0.5, 0.5), 0.5)
	else:
		# If the card is hovered but the mouse is not over it anymore, reverse the animation
		if is_hovered:
			is_hovered = false
			tween_back(0.5)

func tween_back(duration: float):
	# Tween this card back to it's original position.
	tween = create_tween().set_trans(Tween.TRANS_EXPO).set_ease(Tween.EASE_OUT)
	tween.tween_property(self, 'position', original_position, duration)

# Check if the mouse is over a given collision object (shape3d or area3d).
func is_mouse_over(collisionObject3D: CollisionObject3D, excludes = []) -> bool:
	var screen_point = get_viewport().get_mouse_position()
	var from = camera3d.project_ray_origin(screen_point)
	var to = from + camera3d.project_ray_normal(screen_point) * RAY_LENGTH
	var query = PhysicsRayQueryParameters3D.create(from, to)
	query.collide_with_areas = true
	query.collide_with_bodies = true
	for exclude in excludes:
		query.exclude += [exclude.get_rid()]
	var result: Dictionary = get_world_3d().direct_space_state.intersect_ray(query)
	return "rid" in result and result["rid"] == collisionObject3D.get_rid()
