#version 330 core

struct MaterialComponent {
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
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLightComponent {
    vec3 position;

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

#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20

uniform MaterialComponent material;
uniform float time;
uniform vec3 viewPosition;

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLightComponent spotLights[MAX_SPOT_LIGHTS];

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDirection);
vec3 CalcSpotLight(SpotLightComponent light, vec3 normal, vec3 viewDirection);
float CalcLightDiffuseFactor(vec3 normal, vec3 lightDirection);
float CalcLightSpecularFactor(vec3 normal, vec3 lightDirection, vec3 viewDirection);
vec3 Sample(sampler2D sampler);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(viewPosition - FragPos);

    vec3 color = vec3(0.0);
    color += CalcDirectionalLight(directionalLight, normal, viewDirection);

    for (int i = 0; i < pointLightCount; i++)
    {
        color += CalcPointLight(pointLights[i], normal, viewDirection);
    }

    for (int i = 0; i < spotLightCount; i++)
    {
        color += CalcSpotLight(spotLights[i], normal, viewDirection);
    }

    vec3 emissionMap = Sample(material.emission);
    color += emissionMap * (sin(time) * 0.5f + 0.5f) * 2.0;

    FragColor = vec4(color, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);

    // Diffuse
    float diffuseFactor = CalcLightDiffuseFactor(normal, lightDirection);

    // Specular
    float specularFactor = CalcLightSpecularFactor(normal, lightDirection, viewDirection);

    // Result
    vec3 ambient = light.ambient * Sample(material.diffuse);
    vec3 diffuse = light.diffuse * diffuseFactor * Sample(material.diffuse);
    vec3 specular = light.specular * specularFactor * Sample(material.specular);

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - FragPos);

    // Diffuse
    float diffuseFactor = CalcLightDiffuseFactor(normal, lightDirection);

    // Specular
    float specularFactor = CalcLightSpecularFactor(normal, lightDirection, viewDirection);

    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Result
    vec3 ambient = light.ambient * Sample(material.diffuse);
    vec3 diffuse = light.diffuse * diffuseFactor * Sample(material.diffuse);
    vec3 specular = light.specular * specularFactor * Sample(material.specular);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLightComponent light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - FragPos);

    // Diffuse
    float diffuseFactor = CalcLightDiffuseFactor(normal, lightDirection);

    // Specular
    float specularFactor = CalcLightSpecularFactor(normal, lightDirection, viewDirection);

    // Intensity (edge softening)
    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.innerEdge - light.outerEdge;
    float intensity = smoothstep(0.0, 1.0, (theta - light.outerEdge) / epsilon);

    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Result
    vec3 ambient = light.ambient * Sample(material.diffuse);
    vec3 diffuse = light.diffuse * diffuseFactor * Sample(material.diffuse);
    vec3 specular = light.specular * specularFactor * Sample(material.specular);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

float CalcLightDiffuseFactor(vec3 normal, vec3 lightDirection)
{
    return max(dot(normal, lightDirection), 0.0);
}

float CalcLightSpecularFactor(vec3 normal, vec3 lightDirection, vec3 viewDirection)
{
    vec3 reflectDirection = reflect(-lightDirection, normal);
    return pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
}

vec3 Sample(sampler2D sampler)
{
    return vec3(texture(sampler, TexCoords));
}