#include <gtest/gtest.h>

#include "GildedRose.h"

class GildedRoseTest : public testing::Test {
public:
   static const int QUALITY_DELTA = 1;
   static const int PASS_QUALITY_DELTA = 2;
   static const int PASS_SCALPER_QUALITY_DELTA = 3;
    static const int SELL_IN = 5;
    static const int QUALITY = 10;
    static const int QUALITY_CAP = 50;
    static const int SULFURAS_QUALITY = 80;
    std::string m_item_name;

    GildedRoseTest(std::string item_name) {
      m_item_name = item_name;
    }

    Item GetUpdatedItem(int sell_in, int quality) {
        Item item(m_item_name.c_str(), sell_in, quality);
        std::vector<Item> items;
        items.push_back(item);
        GildedRose app(items);
        app.updateQuality();
        return app.items[0];
    }
};

class GildedRoseGenericItem : public GildedRoseTest{
public:
    GildedRoseGenericItem() : GildedRoseTest("foo") {}
};
class GildedRoseBrieItem : public GildedRoseTest{
public:
  GildedRoseBrieItem() : GildedRoseTest(GildedRose::AGED_BRIE_NAME){}
};
class GildedRoseSulfurasItem : public GildedRoseTest{
public:
  GildedRoseSulfurasItem() : GildedRoseTest(GildedRose::SULFURAS_NAME){}
};

const int GildedRoseTest::QUALITY;
const int GildedRoseTest::QUALITY_CAP;
const int GildedRoseTest::SELL_IN;
const int GildedRoseTest::SULFURAS_QUALITY;

TEST_F(GildedRoseGenericItem,  NormalItemQualityDecreasesBeforeSellIn) {
    EXPECT_EQ(QUALITY - QUALITY_DELTA, GetUpdatedItem(SELL_IN, QUALITY)
       .quality);
}

TEST_F(GildedRoseGenericItem,  SellInDecreases) {
    EXPECT_EQ(SELL_IN - 1, GetUpdatedItem(SELL_IN, QUALITY).sellIn);
}

TEST_F(GildedRoseGenericItem,  NormalItemQualityDecrease2xAfterSellIn) {
    EXPECT_EQ(QUALITY - 2* QUALITY_DELTA, GetUpdatedItem(0, QUALITY).quality);
}

TEST_F(GildedRoseGenericItem,  ItemQualityNeverNegative) {
    EXPECT_EQ(0, GetUpdatedItem(SELL_IN, 0).quality);
}

TEST_F(GildedRoseGenericItem,  ItemQualityNeverNegativeWhenSellInZero) {
    EXPECT_EQ(0, GetUpdatedItem(0, 1).quality);
}

TEST_F(GildedRoseBrieItem,  AgedBrieQualityIncreases)
{
  ASSERT_LT(QUALITY, QUALITY_CAP);
  EXPECT_EQ(QUALITY + QUALITY_DELTA, GetUpdatedItem(SELL_IN, QUALITY).quality);
}

TEST_F(GildedRoseBrieItem,  AgedBrieQualityHasCeiling)
{
  EXPECT_EQ(QUALITY_CAP, GetUpdatedItem(SELL_IN, QUALITY_CAP).quality);
}

TEST_F(GildedRoseBrieItem,  ExpiredAgedBrieQualityHasCeiling)
{
  EXPECT_EQ(QUALITY_CAP, GetUpdatedItem(0, QUALITY_CAP - 1).quality);
  EXPECT_EQ(QUALITY_CAP, GetUpdatedItem(0, QUALITY_CAP).quality);
}

TEST_F(GildedRoseSulfurasItem,  SulfurasQualityNeverDecreases)
{
  EXPECT_EQ(SULFURAS_QUALITY, GetUpdatedItem(0, SULFURAS_QUALITY).quality);
}

class GildedRoseBackstagePassesItem : public GildedRoseTest{
public:
  GildedRoseBackstagePassesItem() : GildedRoseTest(GildedRose::BACKSTAGE_PASSES_NAME){}
};

TEST_F(GildedRoseBackstagePassesItem,  PassesIncreaseInQualityBeforeSellIn)
{
  EXPECT_EQ(QUALITY + QUALITY_DELTA, GetUpdatedItem(15, QUALITY).quality);
}

TEST_F(GildedRoseBackstagePassesItem,  PassesIncreaseInQualityByTwoLessThanTenDays)
{
  for(int sellin = 10; sellin > 5; sellin--) {
    EXPECT_EQ(QUALITY + PASS_QUALITY_DELTA, GetUpdatedItem(sellin, QUALITY).quality);
  }
}

TEST_F(GildedRoseBackstagePassesItem,  PassesIncreaseInQualityByThreeLessThanFiveDays)
{
  for(int sellin = 5; sellin > 0; sellin--) {
    EXPECT_EQ(QUALITY + PASS_SCALPER_QUALITY_DELTA, GetUpdatedItem(sellin, QUALITY).quality);
  }
}

TEST_F(GildedRoseBackstagePassesItem,  PassesGotoZeroAfterConcert)
{
  EXPECT_EQ(0, GetUpdatedItem(0, QUALITY).quality);
}

void example()
{
    vector<Item> items;
    items.push_back(Item("+5 Dexterity Vest", 10, 20));
    items.push_back(Item(GildedRose::AGED_BRIE_NAME, 2, 0));
    items.push_back(Item("Elixir of the Mongoose", 5, 7));
    items.push_back(Item(GildedRose::SULFURAS_NAME, 0, GildedRoseTest::SULFURAS_QUALITY));
    items.push_back(Item(GildedRose::BACKSTAGE_PASSES_NAME, 15, 20));
    items.push_back(Item("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
    app.updateQuality();
}
