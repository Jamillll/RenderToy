#include "Texture.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace RenderToy
{
	enum MaterialPropertyType
	{
		NORMALS = 0,
		DIFFUSE,
		SPECULAR,
		ROUGHNESS,
	};

	class MaterialProperty
	{
	private:
		std::unique_ptr<Texture> m_Texture = nullptr;
		glm::vec4 m_Value = glm::vec4(0, 0, 0, 0);

		bool m_UsesTexture;
		MaterialPropertyType m_Type;

	public:

		bool UsesTexture();

		void SetType(MaterialPropertyType type);
		void UseTexture(const std::string& name, bool flipped);
		void UseValue(glm::vec4 value);

		MaterialPropertyType GetType() const;
		const Texture& GetTexture() const;
		const glm::vec4& GetValue() const;

		MaterialProperty();
		MaterialProperty(MaterialPropertyType type, const std::string& name, bool flipped);
		MaterialProperty(MaterialPropertyType type, glm::vec4 value);
		~MaterialProperty();
	};

	class Material : public Asset
	{
	private:
		MaterialProperty m_Normals;
		MaterialProperty m_Diffuse;
		MaterialProperty m_Specular;
		MaterialProperty m_Roughness;

	public:
		Material();

		void SetProperty(MaterialPropertyType type, const std::string& textureName, bool flipped);
		void SetProperty(MaterialPropertyType type, glm::vec4 value);

		MaterialProperty& GetProperty(MaterialPropertyType type);
	};
}