
 #version 330

in vec4 pos;
out vec4 fColor;

void main()
{
    //1
	//fColor = vec4(1.0,0.0,0.0,1.0); //red, green,blue ���ڸ� �ٲ㼭 ���� �ٲܼ� �ִ�. 
    //2
    //vec4(pos.x/2+0.5,pos.y/2+0.5,0,1.0);
    
    
     
     float x = pos.x;
     float y= pos.y;
     float r = sqrt(x*x + y+y);
     
     fColor = vec4(r,r,r,1.0);
     
}