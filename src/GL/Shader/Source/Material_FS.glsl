#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirectionalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
    float innerEdge;
    float outerEdge;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform float time;

in vec3 FragPos;
in vec3 Normal;
in vec3 PointLightPos;
in vec3 SpotLightPos;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);

    vec3 emissionMap = vec3(texture(material.emission, TexCoords));
    vec3 emission = emissionMap * (sin(time) * 0.5f + 0.5f) * 2.0;

    vec3 spotLightDir = normalize(SpotLightPos - FragPos);

    // Ambient
    vec3 ambient = spotLight.ambient * texture(material.diffuse, TexCoords).rgb;

    // Diffuse
    float diff = max(dot(norm, spotLightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // Specular
    vec3 reflectDir = reflect(-spotLightDir, norm);
    float spec = pow(max(dot(spotLightDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * texture(material.specular, TexCoords).rgb;

    // Intensity (spot light edge softening)
    float theta = dot(spotLightDir, normalize(-spotLight.direction));
    float epsilon = spotLight.innerEdge - spotLight.outerEdge;
    float intensity = smoothstep(0.0, 1.0, (theta - spotLight.outerEdge) / epsilon);
    diffuse *= intensity;
    specular *= intensity;

    // Attenuation
    float distance = length(SpotLightPos - FragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}
