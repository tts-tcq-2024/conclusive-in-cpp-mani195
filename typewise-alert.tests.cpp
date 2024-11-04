#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, PassiveCoolingBreach) 
{
    std::unique_ptr<CoolingContext> coolingObj = std::make_unique<CoolingContext>(std::make_unique<PassiveCooling>());
    EXPECT_EQ(coolingObj->inferBreach(-1), BreachType::TOO_LOW);
    EXPECT_EQ(coolingObj->inferBreach(36), BreachType::TOO_HIGH);
    EXPECT_EQ(coolingObj->inferBreach(30), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, HiActiveCoolingBreach) 
{
    std::unique_ptr<CoolingContext> coolingObj = std::make_unique<CoolingContext>(std::make_unique<HiActiveCooling>());
    EXPECT_EQ(coolingObj->inferBreach(-1), BreachType::TOO_LOW);
    EXPECT_EQ(coolingObj->inferBreach(46), BreachType::TOO_HIGH);
    EXPECT_EQ(coolingObj->inferBreach(30), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, MediumActiveCoolingBreach) 
{
    std::unique_ptr<CoolingContext> coolingObj = std::make_unique<CoolingContext>(std::make_unique<MedActiveCooling>());
    EXPECT_EQ(coolingObj->inferBreach(-1), BreachType::TOO_LOW);
    EXPECT_EQ(coolingObj->inferBreach(41), BreachType::TOO_HIGH);
    EXPECT_EQ(coolingObj->inferBreach(40), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, ControllerAlert) 
{
    std::unique_ptr<CoolingContext> coolingObj = std::make_unique<CoolingContext>(std::make_unique<MedActiveCooling>());
    BreachType actualBreachType = coolingObj->inferBreach(-1);
    EXPECT_EQ(actualBreachType, BreachType::TOO_LOW);
    std::unique_ptr<Alerter> alerter = std::make_unique<Alerter>(std::make_unique<ControllerAlert>());
    alerter->report(actualBreachType);
}

TEST(TypeWiseAlertTestSuite, EmailAlertForHigh) 
{
    std::unique_ptr<CoolingContext> coolingObj = std::make_unique<CoolingContext>(std::make_unique<MedActiveCooling>());
    BreachType actualBreachType = coolingObj->inferBreach(41);
    EXPECT_EQ(actualBreachType, BreachType::TOO_HIGH);
    std::unique_ptr<Alerter> alerter = std::make_unique<Alerter>(std::make_unique<EmailAlert>());
    alerter->report(actualBreachType);
}

TEST(TypeWiseAlertTestSuite, NoEmailAlertForNormal) 
{
    std::unique_ptr<CoolingContext> coolingObj = std::make_unique<CoolingContext>(std::make_unique<PassiveCooling>());
    BreachType actualBreachType = coolingObj->inferBreach(30);
    EXPECT_EQ(actualBreachType, BreachType::NORMAL);
    std::unique_ptr<Alerter> alerter = std::make_unique<Alerter>(std::make_unique<EmailAlert>());
    alerter->report(actualBreachType);
}
