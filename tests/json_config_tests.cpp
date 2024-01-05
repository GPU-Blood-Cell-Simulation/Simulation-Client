#include <gtest/gtest.h>

#include <exception>
#include <nlohmann/json.hpp>

#include "../src/serializable/general_config/general_config.hpp"

using namespace serializable;
using json = nlohmann::json;


TEST(SimulationConfigTests, LoadSimulationConfigPositive)
{
    SimulationConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(SimulationConfig config2 = j.template get<SimulationConfig>());
}

TEST(SimulationConfigTests, LoadSimulationConfigMissing)
{
    SimulationConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.erase("o.dt"));
    EXPECT_THROW(SimulationConfig config2 = j.template get<SimulationConfig>(), std::exception);
}

TEST(SimulationConfigTests, LoadSimulationConfigWrongValue)
{
    SimulationConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.update({{"o.dt", "sometext"}}, false));
    EXPECT_THROW(SimulationConfig config2 = j.template get<SimulationConfig>(), std::exception);
}


TEST(PhysicsConfigTests, LoadPhysicsConfigPositive)
{
    PhysicsConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(PhysicsConfig config2 = j.template get<PhysicsConfig>());
}

TEST(PhysicsConfigTests, LoadPhysicsConfigMissing)
{
    PhysicsConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.erase("o.gravity"));
    EXPECT_THROW(PhysicsConfig config2 = j.template get<PhysicsConfig>(), std::exception);
}

TEST(PhysicsConfigTests, LoadPhysicsConfigWrongValue)
{
    PhysicsConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.update({{"o.gravity", "sometext"}}, false));
    EXPECT_THROW(PhysicsConfig config2 = j.template get<PhysicsConfig>(), std::exception);
}


TEST(GraphicsConfigTests, LoadGraphicsConfigPositive)
{
    GraphicsConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(GraphicsConfig config2 = j.template get<GraphicsConfig>());
}

TEST(GraphicsConfigTests, LoadGraphicsConfigMissing)
{
    GraphicsConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.erase("o.cameraRotationSpeed"));
    EXPECT_THROW(GraphicsConfig config2 = j.template get<GraphicsConfig>(), std::exception);
}

TEST(GraphicsConfigTests, LoadGraphicsConfigWrongValue)
{
    GraphicsConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.update({{"o.cameraRotationSpeed", "sometext"}}, false));
    EXPECT_THROW(GraphicsConfig config2 = j.template get<GraphicsConfig>(), std::exception);
}


TEST(GeneralConfigTests, LoadGeneralConfigPositive)
{
    GeneralConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(GeneralConfig config2 = j.template get<GeneralConfig>());
}

TEST(GeneralConfigTests, LoadGeneralConfigMissing)
{
    GeneralConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.erase("o.simulation"));
    EXPECT_THROW(GeneralConfig config2 = j.template get<GeneralConfig>(), std::exception);
}

TEST(GeneralConfigTests, LoadGeneralConfigWrongValue)
{
    GeneralConfig config1;
    json j;
    EXPECT_NO_THROW(j = config1);
    EXPECT_NO_THROW(j.update({{"o.simulation", "sometext"}}, false));
    EXPECT_THROW(GeneralConfig config2 = j.template get<GeneralConfig>(), std::exception);
}