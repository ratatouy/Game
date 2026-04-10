// Source - https://stackoverflow.com/a/64845819
// Posted by Spektre, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-21, License - CC BY-SA 4.0

//---------------------------------------------------------------------------
// Fragment
//---------------------------------------------------------------------------
#version 420 core
//---------------------------------------------------------------------------
uniform sampler2D currentTexture;  // Our render texture
uniform float r;                   // blur radius
//---------------------------------------------------------------------------
void main()
{
    gl_FragColor = vec4( .5, 1., 0., 1. );
}
//---------------------------------------------------------------------------
