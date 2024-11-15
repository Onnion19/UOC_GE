#define MAXBONES 29

cbuffer SceneConstantBuffer : register( b0 )
{
	matrix m_View;
	matrix m_Projection;
	float4 m_CameraRightVector;
	float4 m_CameraUpVector;
}

cbuffer ObjectConstantBuffer : register( b1 )
{
	matrix m_World;
	float4 m_BaseColor;
	float4 m_DebugRenderScale;
}

cbuffer AnimatedModelConstantBuffer : register( b2 )
{
	matrix m_Bones[MAXBONES];
}
