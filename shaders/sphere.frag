#version 330 core

uniform mat4 model_view;
uniform mat4 projection;
uniform float cursorX;
uniform float cursorY;
uniform float near;
uniform float far;

in vec3 out_color;
in vec3 position;
in vec3 vN;

out vec3 color;


vec3 CalcLVector(vec4 source_position, vec3 pos)
{
	return normalize(source_position.xyz - pos.xyz);
}

vec3 HalfAngle(vec3 l, vec3 e)
{
	return normalize(l + e);
}

vec4 Diffuse(vec3 l, vec3 n, vec4 clr, vec4 direction)
{
	vec3 d = normalize(direction).xyz;
	float co = cos(3.14);

	if (dot(-l,d) >  co) 
		return max(dot(l,n),0.0) * vec4(0.5,0.5,0.5,0.0) * clr;
	else
		return vec4(0,0,0,1);
}

vec4 Specular(vec3 n, vec3 h, vec4 clr,vec3 l, vec4 direction)
{
	vec3 d = normalize(direction).xyz;
	float co = cos(3.14);

	if (dot(-l,d) >  co) 
		return pow(max(dot(n,h),0.0),100) * vec4(1.0,1.0,1.0,0.0) * clr;
	else
		return vec4(0,0,0,1);	
}

float random(float x)
{
	float i = floor(x);
	float f = fract(x);
	float u = f * f *  (3.0 - 2.0 * f);
	
	return mix(i * 0.5, (i + 1.0) * 0.5, u);
}

void main(){

	vec3 N = normalize(vN.xyz);
	//
	
	/*vec4 lightsourceposition = vec4(0,20,200,1);
	vec4 lightsourcecolor = vec4(1,0,0,1);
	vec4 lightsourcedirection = vec4(0,0,-1,0);
	
	vec4 ambient_light = vec4(0.2,0.2,0.2,1.0);
	
	vec3 E = -normalize(position.xyz);
	vec3 L = CalcLVector(lightsourceposition, position);
	vec3 H = HalfAngle(L,E);
	
	
	
	vec4 amb =  ambient_light;
	vec4 diff = Diffuse(L,N,lightsourcecolor,lightsourcedirection);
	vec4 spec = Specular(N,H,lightsourcecolor,L,lightsourcedirection);
	
	*/
	


	float x = (2.0f * cursorX) / 1024 - 1.0f;
	float y = 1.0f - (2.0f * cursorY) / 1024;
	float z = 1.0f;
	vec3 ray_nds = vec3(x, y, z);
	
	vec4 ray_clip = vec4(ray_nds.xy, -1.0, 1.0);
	
	vec4 ray_eye = inverse(projection) * ray_clip;
	ray_eye = vec4(ray_eye.xy, -1.0, 0.0);
	
	vec3 ray_wor = (inverse(model_view) * ray_eye).xyz;
	// don't forget to normalize the vector at some point	
	ray_wor = normalize(ray_wor);
	
	vec3 ray_vor_origin = vec3(0,20,200);
	
	vec3 center = position;
	
	vec3 oc = ray_vor_origin - center;
	
	float a = dot(ray_wor,ray_wor);
	float b = dot(oc, ray_wor);
	float c = dot(oc, oc) - 1 * 1;
	
	float discriminant = b * b - a * c;
	
	if (discriminant > 0)
	{
		float temp1 = (-b - sqrt(b * b - a * c)) / a;
		float temp2 = (-b + sqrt(b * b - a * c)) / a;
		
		if (temp1 < far && temp1 > near)
		{
			vec3 N = normalize(ray_wor * temp1 - vec3(0,0,-1));
			color = 0.5f * vec3(N.x + 1, N.y + 1, N.z + 1);
		}
		else if (temp2 < far && temp2 > near)
		{
			vec3 N = normalize(ray_wor * temp2 - vec3(0,0,-1));
			color = 0.5f * vec3(N.x + 1, N.y + 1, N.z + 1);
		}
		else
		{
			color = vec3(0,1,0);
		}
	}
	else
	{
		//vec3 target = position + N + random_in_unit_sphere();
		
		vec2 st = gl_FragCoord.xy/10.0;
	
		color = vec3(1,1,1);
	}
	
	//color = vec4(amb + diff + spec).xyz;
}
