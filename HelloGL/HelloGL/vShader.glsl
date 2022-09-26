#version 330

in vec4 vPosition;  // in 인자    
out vec4 pos;   //fShader 가 in으로 받음 -> fshader 폴더로 이동

void main()
{
	gl_Position = vPosition*0.5;     //vShader 에서의 코드
    gl_Position.w =1.0f;
    pos = vPosition;    //fShader로 전달 가능 
    //glsl language 이다. vs 에서 compile에 영향을 주지 않음.
    
    // 좌표가 0.5 만큼 절반이 될 것이다. 전체 화면의 0.5 사이즈 축소
    // shader 를 바꾼 행위이다. 

}