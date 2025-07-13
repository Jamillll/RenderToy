#include "Material.h"

namespace RenderToy
{
	Material::Material() {}

	void Material::SetProperty(MaterialPropertyType type, const std::string& textureName, bool flipped)
	{
		switch (type)
		{
		case RenderToy::NORMALS:
			m_Normals.SetType(type);
			m_Normals.UseTexture(textureName, flipped);
			break;

		case RenderToy::DIFFUSE:
			m_Diffuse.SetType(type);
			m_Diffuse.UseTexture(textureName, flipped);
			break;

		case RenderToy::SPECULAR:
			m_Specular.SetType(type);
			m_Specular.UseTexture(textureName, flipped);
			break;

		case RenderToy::ROUGHNESS:
			m_Roughness.SetType(type);
			m_Roughness.UseTexture(textureName, flipped);
			break;
		}
	}

	void Material::SetProperty(MaterialPropertyType type, glm::vec4 value)
	{
		switch (type)
		{
		case RenderToy::NORMALS:
			m_Normals.SetType(type);
			m_Normals.UseValue(value);
			break;

		case RenderToy::DIFFUSE:
			m_Diffuse.SetType(type);
			m_Diffuse.UseValue(value);
			break;

		case RenderToy::SPECULAR:
			m_Specular.SetType(type);
			m_Specular.UseValue(value);
			break;

		case RenderToy::ROUGHNESS:
			m_Roughness.SetType(type);
			m_Roughness.UseValue(value);
			break;
		}
	}

	MaterialProperty& Material::GetProperty(MaterialPropertyType type)
	{
		switch (type)
		{
		case RenderToy::NORMALS:
			return m_Normals;
		case RenderToy::DIFFUSE:
			return m_Diffuse;
		case RenderToy::SPECULAR:
			return m_Specular;
		case RenderToy::ROUGHNESS:
			return m_Roughness;
		}
	}

	MaterialProperty::MaterialProperty()
		: m_Type(MaterialPropertyType::NORMALS), m_UsesTexture(false), m_Value(glm::vec4(0, 0, 0, 0))
	{}

	MaterialProperty::MaterialProperty(MaterialPropertyType type, const std::string& name, bool flipped)
		: m_Type(type), m_UsesTexture(true), m_Texture(std::make_unique<Texture>(name, flipped)) {}

	MaterialProperty::MaterialProperty(MaterialPropertyType type, glm::vec4 value)
		: m_Type(type), m_UsesTexture(false), m_Value(value) {}

	bool MaterialProperty::UsesTexture()
	{
		return m_UsesTexture;
	}

	void MaterialProperty::SetType(MaterialPropertyType type)
	{
		m_Type = type;
	}

	void MaterialProperty::UseTexture(const std::string& name, bool flipped)
	{
		m_Value = glm::vec4(0, 0, 0, 0);

		m_Texture.reset();
		m_Texture = std::make_unique<Texture>(name, flipped);

		m_UsesTexture = true;
	}

	void MaterialProperty::UseValue(glm::vec4 value)
	{
		m_Texture.reset();
		m_UsesTexture = false;

		m_Value = value;
	}

	MaterialPropertyType MaterialProperty::GetType() const
	{
		return m_Type;
	}

	const Texture& MaterialProperty::GetTexture() const
	{
		return *m_Texture.get();
	}

	const glm::vec4& MaterialProperty::GetValue()const
	{
		return m_Value;
	}

	MaterialProperty::~MaterialProperty()
	{
		if (m_UsesTexture)
			m_Texture.reset();
	}
}
