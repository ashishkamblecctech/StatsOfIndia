varying lowp vec4 col;
varying mediump vec3 Normal;

void main() {
    mediump vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));

    lowp vec3 ambientColor = vec3(0.6, 0.6, 0.6);
    lowp vec3 ambient = ambientColor * col.rgb;

    mediump float intensity = max(dot(Normal, lightDir), 0.3);
    lowp vec3 diffuseColor = vec3(1.2, 1.2, 1.2);
    lowp vec3 diffuse = diffuseColor * col.rgb * intensity;

    lowp vec3 finalColor = ambient + diffuse;
    gl_FragColor = vec4(finalColor, col.a);
}
