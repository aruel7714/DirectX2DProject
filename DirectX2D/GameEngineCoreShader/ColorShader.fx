// 버텍스 쉐이더 입니다.


float4 ColorShader_VS(float4 pos : POSITION) : SV_Position
{
    return pos /** WorldViewProjection*/;
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}