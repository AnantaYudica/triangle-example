attribute vec4 aPosition;
attribute vec4 acolor;

varying vec4 vColor;

 void main()
 {
    gl_Position = aPosition;
    vColor = acolor;
 }