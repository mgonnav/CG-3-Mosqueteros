#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

// texture samplers
uniform sampler2D main_image_texture;
uniform sampler2D background_texture;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	//FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0f);
	
	// this work
	//FragColor = vec4(ourColor, 1.0f);
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	FragColor = texture(main_image_texture, TexCoord);
}