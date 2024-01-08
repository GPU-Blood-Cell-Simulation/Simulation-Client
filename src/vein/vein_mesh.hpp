#pragma once

#include "../graphics/shader.hpp"
#include "../serializable/cpp_serializable.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

#include <iostream>

namespace vein
{
    /// <summary>
    /// A base mesh class that is not intended to be drawn - it's used only as a container
    /// </summary>
    class TempMesh
    {
    public:
        /// <summary>
        /// A constructor moving both positions and indices
        /// </summary>
        /// <param name="positions">An rvalue ref to a vector of mesh vertex position</param>
        /// <param name="indices">An rvalue ref to a vector of mesh indices</param>
        TempMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices);

        /// <summary>
        /// A constructor moving only positions and copying indices
        /// </summary>
        /// <param name="positions">An rvalue ref to a vector of mesh vertex position</param>
        /// <param name="indices">An regular reference to a vector of mesh indices</param>
        TempMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices);
        virtual ~TempMesh() {}

        std::vector<glm::vec3> positions;
        std::vector<unsigned int> indices;
    protected:
        TempMesh() {}
    };

    /// <summary>
    /// A standard mesh object drawable by OpenGl. Has GPU buffers associated with it
    /// </summary>
    class VeinMesh : public TempMesh {
    public:
		/// <summary>
	    /// A constructor moving both positions and indices
	    /// </summary>
	    /// <param name="positions">An rvalue ref to a vector of mesh vertex position</param>
	    /// <param name="indices">An rvalue ref to a vector of mesh indices</param>
        VeinMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices);

        /// <summary>
        /// A constructor moving only positions and copying indices
        /// </summary>
        /// <param name="positions">An rvalue ref to a vector of mesh vertex position</param>
        /// <param name="indices">An regular reference to a vector of mesh indices</param>
        VeinMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices);
        virtual ~VeinMesh() override;

        // constructors needed for json serialization
        VeinMesh() = default;
        VeinMesh(const VeinMesh&) = default;
        VeinMesh(VeinMesh&&) = default;
        VeinMesh& operator=(const VeinMesh&) = default;
        VeinMesh& operator=(VeinMesh&&) = default;

        /// <summary>
        /// Pass the mesh data to OpenGL
        /// </summary>
        void setupMesh();

        /// <summary>
        /// Draws the object on the screen
        /// </summary>
        /// <param name="shader">A shader that will be used for this draw call</param>
        void draw(const Shader* shader) const;

    private:
        /// <summary>
        /// OpenGL Render data
        /// </summary>
        unsigned int VAO = 0, VBO = 0, EBO = 0;

        /// <summary>
        /// Whether this instance is an owner of gpu buffers (has been initialized by setupMesh())
        /// </summary>
        bool vOwner = false;
    };

    class SerializableMesh : public TempMesh, public serializable::ICppSerializable
    {
    public:
        /// <summary>
        /// An empty constructor for SerializableMesh - for appending segments to it later on
        /// </summary>
        SerializableMesh() {}

        /// <summary>
        /// Serialize all vertices and indices to a .hpp file
        /// </summary>
        virtual void serializeToCpp() const override;
        void addEnding(const glm::vec3& endingPosition, float radius);

    private:
        std::vector<glm::vec3> endingPositions;
        std::vector<float> endingRadii;
    };
}