struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
VOut main_vs(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;
    output.position = position;
    output.color = color;
    return output;
}
float4 main_ps(float4 position : SV_POSITION, 
    float4 color : COLOR) : SV_TARGET
{
    return color;
}