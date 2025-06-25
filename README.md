# RenderToy

RenderToy is a scene renderer application that can load in and render custom models, shaders and lighting. You will be able to save scenes as files, load them in and then use the editor to change them as you see fit. I am currently using Dear ImGui for the UI, Assimp for model loading and glad and glfw for graphics and window functions. Below is a screenshot of how this project currently looks. It is in very early stages right now but I am steadily working towards a 1.0 release.

My reason for making this project is to become more familiar with the OpenGL graphics specification and gain a better understanding of its graphic's pipeline, as well as giving me a space to toy with and experiment with any rendering techniques that interest me in the future, hence the name.

![alt text](https://github.com/Jamillll/RenderToy/blob/main/Screenshot.png)

## Steps towards 1.0 Release
My current plan for RenderToy 1.0 is for it to be a simple model loader and scene viewer. I want to make the program easy to use before I delve into more advanced graphics topics such as lighting.

## TODO
- Improve Model Loading
- Finish the Asset Tray
- Create simple icons to use in the Asset Tray for Model Assets
- Add a lot more information to the Asset Properties Panel
- Create a system for saving and loading projects
- Finish the object creation menu

## BUGS TO FIX
- Model rotation and point of rotation not working correctly
- Scene View Camera jumping on entry
