//
//
//run command g++ error.cpp -lglut -lGL -lGLEW -g


#include "initShaders.h"
using namespace std;
int counter=0;

//vertexIDs
GLuint vaoID, vboID;// the buffers that are going to be linked too
//vertices
GLfloat Triangle[]={	0.5f	,	-0.5f	,	0.0f	,
				0.0f	,	0.5f	,	0.0f	,
				-0.5f	,	-0.5f	,	0.0f
};// vertices that are drawn x,y,z ...

GLfloat Square[] = {	-0.5f	,	-0.5f	,	0.5f	,
				-0.5f	,	0.5f	,	0.5f	,
				0.5f	,	0.5f	,	0.5f	,
				0.5f	,	-0.5f	,	0.5f		
};// vertices that are drawn x,y,z ..

GLfloat Trapezoid[] = {	-0.75f,	-0.5f	,	0.5f	,
				-0.25f,	0.5f	,	0.5f	,
				0.75f	,	0.5f	,	0.5f	,
				0.25f	,	-0.5f	,	0.5f		
};// vertices that are drawn x,y,z ..

//indices of triangle
GLubyte indices[3]={0,1,2};

//opengl 4
void triangle(){
  glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);//allocates the memory of the vertices

 ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw

  glDrawArrays(GL_TRIANGLES, 0, 3);//draws array
  glFlush();//makes sure the prcesses finish
}

void square(){
  glClear(GL_COLOR_BUFFER_BIT);//clear screen

  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(Square), Square, GL_STATIC_DRAW);//allocates the memory of the vertices

 ShaderInfo shaders[]={//create the shader specified by my initshaders input
  { GL_VERTEX_SHADER , "vertexshader2.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader2.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  	  	
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
  
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableVertexAttribArray(0);
  glFlush();//make sure the processes finish
}

void trapezoid(){
  glClear(GL_COLOR_BUFFER_BIT);//clear screen

  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(Trapezoid), Trapezoid, GL_STATIC_DRAW);//allocates the memory of the vertices

 ShaderInfo shaders[]={//create the shader specified by my initshaders input
  { GL_VERTEX_SHADER , "vertexshader3.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader3.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  	  	
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
  
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableVertexAttribArray(0);
  glFlush();//make sure the processes finish
}

void drawscene(){
  switch(counter%3){//easy way to switch throw functions
    case 0:
      glutDisplayFunc(trapezoid);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 1:
      glutDisplayFunc(triangle);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 2:
      glutDisplayFunc(square);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
  }
}
//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click changes the shape color
    counter++;
    drawscene();
  }
}

void idle(void){
  glutPostRedisplay();
}

int main(int argc, char **argv){

  //Freeglut window and context management	
  glutInit(&argc, argv);
  glutCreateWindow("Jeffrey Kopra - Shapes");//creates the window with the specified name
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);//specifies the version of opengl
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);//specifies what profile your using


  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}

