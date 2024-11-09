```mermaid
---
title: ZPG Projekt 
---
classDiagram
    InputHandler --|> ISubject
    Camera --|> ISubject

    Camera --|> IObserver
    DrawableObject --|> IObserver

    class App{

    }

    class InputHandler{

    }

    class Camera{
        
    }
    
    class DrawableObject{
        
    }

    class Model{
        
    }

    class ModelManager{
        
    }

    class Scene{

    }

    class ShaderLoader{
        
    }

    class ShaderManager{
        
    }

    class ShaderProgram{
        
    }

    class Scale{
        
    }

    class Rotate{
        
    }

    class Translate{
        
    }

    class ITransformation{
        
    }

    class IObserver{
        
    }

    class ISubject{
        
    }
```