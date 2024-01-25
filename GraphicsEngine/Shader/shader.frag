#version 330 core
in vec4 vColor;
in vec3 normal;
in vec3 fragPos;
out vec4 color;
void main(){
    vec3 lightColor = vec3(250.0/255, 214.0/255, 165.0/255);
    vec3 normNorm = normalize(normal);
    if(normal == vec3(0.0, 0.0, 0.0)){
         color = vColor;
    }else{
        vec3 lightPos = vec3(0.0, 2500.0, 2500.0);
        vec3 lightDir = normalize(lightPos - fragPos);
        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * lightColor;
        float diff = max(dot(normNorm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        color = vec4((diffuse+ambient)*vec3(vColor.x, vColor.y, vColor.z), 1.0);
    }
}