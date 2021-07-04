#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform PointLight pointLight;
uniform DirectionalLight directionalLight;
uniform float time;

in vec3 FragPos;
in vec3 Normal;
in vec3 PointLightPos;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    float distance = length(PointLightPos - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    // TODO: extract global ambient light to a global setting (scene/environment property)
    vec3 ambient = (pointLight.ambient * attenuation) * directionalLight.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 norm = normalize(Normal);

    // Point light diffuse
    vec3 pointLightDir = normalize(PointLightPos - FragPos);
    float pointLightDiff = max(dot(norm, pointLightDir), 0.0);

    // Directional light diffuse
    vec3 directionalLightDir = normalize(-directionalLight.direction);
    float directionalLightDiff = max(dot(norm, directionalLightDir), 0.0);

    // Final diffuse
    vec3 diffuse = (pointLight.diffuse * pointLightDiff) * (directionalLight.diffuse * directionalLightDiff) * vec3(texture(material.diffuse, TexCoords));
    diffuse *= attenuation;

    vec3 viewDir = normalize(-FragPos);

    // Point light specular
    vec3 pointLightReflectDir = reflect(-pointLightDir, norm);
    float pointLightSpec = pow(max(dot(viewDir, pointLightReflectDir), 0.0), material.shininess);

    // Directional light specular
    vec3 directionalLightReflectDir = reflect(-directionalLightDir, norm);
    float directionalLightSpec = pow(max(dot(viewDir, directionalLightReflectDir), 0.0), material.shininess);

    // Final specular
    vec3 specularMap = vec3(texture(material.specular, TexCoords));
    vec3 specular = (pointLight.specular * pointLightSpec) * (directionalLight.specular * directionalLightSpec) * specularMap;
    specular *= attenuation;

    vec3 emissionMap = vec3(texture(material.emission, TexCoords));
    vec3 emission = emissionMap * (sin(time) * 0.5f + 0.5f) * 2.0;

    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}
