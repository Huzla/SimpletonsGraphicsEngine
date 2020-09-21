#version 330 core
out vec4            FragColor;

in vec2             TexCoord;
in vec3             FragPos;
in vec3             Normal;

uniform sampler2D   texture1;
uniform sampler2D   texture2;
uniform vec3        lightColor;
uniform vec3        lightPos;


void main()
{
    vec4 objColor   = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, 1.0f - TexCoord.y)), 0.2f);
    vec3 ambient    = 0.1f * lightColor;

    vec3 norm       = normalize(Normal);
    vec3 lightDir   = normalize(lightPos - FragPos);
    vec3 diffuse    = max(dot(norm, lightDir), 0.0f)*lightColor;

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5f * spec * lightColor;

    vec3 result     = (ambient + diffuse + specular) * objColor.xyz;
    FragColor       = vec4(result, objColor.w);
}