uniform sampler2D tex;
uniform vec4 fogColor;
uniform float fogDensity;
varying vec4 light;
varying float theZ;
void main()
{
    vec4 texel;
    texel = texture2D(tex,gl_TexCoord[0].st);

    texel *= light;

	const float LOG2 = 1.442695;
	float z = (gl_FragCoord.z / gl_FragCoord.w);

	float fogFactor = exp2( -fogDensity * 
						fogDensity * 
						z * 
						z * 
				   LOG2 );
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	gl_FragColor = fogFactor * texel + (1.0-fogFactor)*fogColor;


	//gl_FragColor = mix(fogColor, texel, fogFactor );

}
