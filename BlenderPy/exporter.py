import os
import bpy
import tempfile
from shutil import copyfile
from mathutils import Matrix

def ExportUGXandUAX(exportOutName):
    outName = exportOutName
    
    bpy.ops.object.mode_set(mode = 'POSE')            

    for o in bpy.context.scene.objects:
        if o.type == 'ARMATURE':
            for bone in o.pose.bones:
                 bone.matrix_basis = Matrix()
        
                
    with tempfile.TemporaryDirectory() as dir:
        
        bpy.ops.export_scene.fbx(
            filepath=dir + "\\tempMesh.fbx",
            object_types={'MESH'},
            use_selection=False,
            add_leaf_bones=False,
            bake_anim=False,
            use_armature_deform_only=True)
            
        copyfile(dir + "\\tempMesh.fbx", outName + ".fbx")    
        fileDir = dir + "\\tempMesh.fbx"
        outDir = outName + ".ugx"
        os.system("I:\BlenderUGXToolchain\_build\StumpyBlenderUGXExporter.exe " + fileDir + " \"" + outDir + "\" exUGX exGR2 m" )
        
        
        for action in bpy.data.actions:
            for o in bpy.context.scene.objects:
                if o.type == 'ARMATURE':
                    for bone in o.pose.bones:
                        bone.matrix_basis = Matrix()
                    o.animation_data.action = action
                    
                    bpy.ops.export_scene.fbx(
                    filepath=dir + "\\tempMesh_" + action.name + ".fbx",
                    object_types={'ARMATURE'},
                    use_selection=False,
                    add_leaf_bones=False,
                    bake_anim=True,
                    bake_anim_use_all_actions=False,
                    bake_anim_use_nla_strips=False,
                    )
                    
                    fileDir = dir + "\\tempMesh_" + action.name + ".fbx"
                    outDir = outName + "_" + action.name + ".uax"
                    os.system("I:\BlenderUGXToolchain\_build\StumpyBlenderUGXExporter.exe " + fileDir + " \"" + outDir + "\" exUGX exGR2 a" )
        
        
    return;
    
ExportUGXandUAX("C:\\Users\\Jake\\Desktop\\fbx\\New folder\\test")
