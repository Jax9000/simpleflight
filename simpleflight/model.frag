#version 330 core

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos; 

void main()
{    
    //color = vec4(texture(texture_diffuse1, TexCoords));
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;
	vec3 objectColor = vec3(texture(texture_diffuse1, TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;  
	vec3 result = (ambient + diffuse) * objectColor;
	color = vec4(result, 1.0f);
}

