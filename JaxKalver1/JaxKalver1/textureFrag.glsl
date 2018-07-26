#version 330

in  vec2 texCoords;
in  vec3 vertNormal;
in  vec3 lightDir;


out vec4 fragColor;
uniform sampler2D myTexture0;  


void main() { 
	/// I could have passed these in as Uniforms but for simplicity, 
	/// I'll just define them here: specular, diffuse, ambient for the surface material 
	const vec4 ks = vec4(0.5, 0.5, 0.5, 0.0);

	
	/// The reflect() method this most GPU expensive step in this proceedure
	/// The Blinn-Phong method is faster.   	
	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float diff = max(dot(vertNormal, lightDir), 0.0);
	float spec = max(0.0, dot(vertNormal, reflection));
	if(diff != 0.0){
		spec = pow(spec,4.0);
	}
	vec4 kd = texture2D(myTexture0,texCoords);
	vec4 ka = 0.001 * kd;
	fragColor =  ka + (diff * kd) + (spec * ks);
}
