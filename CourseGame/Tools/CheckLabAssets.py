import json
from pathlib import Path
import unreal as ue
checks=[]
def check(name,result):
    checks.append({'name':name,'passed':bool(result)})
    assert result,name
assets=ue.EditorAssetLibrary
root='/Game/Course/Week03/'
move=assets.load_asset(root+'IA_Move'); jump=assets.load_asset(root+'IA_Jump')
context=assets.load_asset(root+'IMC_Gameplay')
check('Move is Axis1D',move.get_editor_property('value_type')==ue.InputActionValueType.AXIS1D)
check('Jump is Boolean',jump.get_editor_property('value_type')==ue.InputActionValueType.BOOLEAN)
mappings=context.get_editor_property('default_key_mappings').get_editor_property('mappings')
check('Seven keyboard and gamepad mappings',len(mappings)==7)
negated=sum(any(isinstance(m,ue.InputModifierNegate) for m in mapping.get_editor_property('modifiers')) for mapping in mappings)
check('Two negated left mappings',negated==2)
cls=ue.load_class(None,root+'BP_RunnerCharacter.BP_RunnerCharacter_C')
defaults=ue.get_default_object(cls)
check('Move assigned',defaults.get_editor_property('move_action')==move)
check('Jump assigned',defaults.get_editor_property('jump_action')==jump)
check('Context assigned',defaults.get_editor_property('gameplay_context')==context)
check('Lab baseline jump hold zero',abs(defaults.get_editor_property('jump_max_hold_time'))<.001)
check('Correct integration baseline',not defaults.get_editor_property('demonstrate_delta_time_bug'))
movement=defaults.get_editor_property('character_movement')
check('Plane enabled',movement.get_editor_property('constrain_to_plane'))
normal=movement.get_plane_constraint_normal()
check('XZ plane',abs(normal.y-1)<.001 and abs(normal.x)<.001 and abs(normal.z)<.001)
check('Fixed facing',not movement.get_editor_property('orient_rotation_to_movement'))
check('Idle assigned',defaults.get_editor_property('idle_animation') is not None)
check('Run assigned',defaults.get_editor_property('run_animation') is not None)
mode_cls=ue.load_class(None,root+'BP_RunnerGameMode.BP_RunnerGameMode_C')
check('Default pawn assigned',ue.get_default_object(mode_cls).get_editor_property('default_pawn_class')==cls)
level=ue.get_editor_subsystem(ue.LevelEditorSubsystem)
check('Saved map reopens',level.load_level('/Game/Course/Maps/L_Week03'))
actors=ue.get_editor_subsystem(ue.EditorActorSubsystem).get_all_level_actors()
check('One player start',sum(isinstance(a,ue.PlayerStart) for a in actors)==1)
check('One collectible',sum(isinstance(a,ue.RunnerPickup) for a in actors)==1)
check('One recovered room',sum(isinstance(a,ue.CourseRoom) for a in actors)==1)
room=next(a for a in actors if isinstance(a,ue.CourseRoom))
check('Blue foreground is nonblocking',room.get_editor_property('foreground').get_collision_enabled()==ue.CollisionEnabled.NO_COLLISION)
for prop in ['floor_collision','left_wall_collision','right_wall_collision']:
    check(prop+' uses BlockAll',str(room.get_editor_property(prop).get_collision_profile_name())=='BlockAll')
world=ue.get_editor_subsystem(ue.UnrealEditorSubsystem).get_editor_world()
check('Level game mode assigned',world.get_world_settings().get_editor_property('default_game_mode')==mode_cls)
receipt={'engine':ue.SystemLibrary.get_engine_version(),'checks':checks,'passed':all(c['passed'] for c in checks)}
file=Path(ue.Paths.project_dir())/'Evidence/Week03/editor-checks.json'
file.parent.mkdir(parents=True,exist_ok=True);file.write_text(json.dumps(receipt,indent=2))
ue.log('WEEK3_EDITOR_CHECKS_PASSED: '+str(len(checks)))

