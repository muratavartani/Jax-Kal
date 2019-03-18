#version 330 core

//layout (location = 0) out vec4 FragColor;
//layout (location = 1) out vec4 BrightColor;

struct Light{
	vec3 lightPos;
	float ambient;
	float diffuse;
	vec3 lightColor;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

uniform sampler2D inputTexture;
uniform vec3 viewPosition;
uniform Light light;

out vec4 color;




void main(){
	//ambient
	vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.lightColor;
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	//vec3 lightDir = normalize(light.lightPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * texture(inputTexture, TexCoords).rgb * light.lightColor;

	//specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.lightColor;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);



    
	
}