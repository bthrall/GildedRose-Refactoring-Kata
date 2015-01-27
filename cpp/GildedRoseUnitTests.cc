#include <gtest/gtest.h>

#include "GildedRose.h"

class GildedRoseTest : public testing::Test {
protected:
    static const int SELL_IN = 5;
    static const int QUALITY = 10;
    static const int QUALITY_CAP = 50;
    vector<Item> m_items;

    Item GetUpdatedItem(const Item &item) {
        m_items.push_back(item);
        GildedRose app(m_items);
        app.updateQuality();
        return app.items[0];
    }

};
const int GildedRoseTest::QUALITY;
const int GildedRoseTest::QUALITY_CAP;
const int GildedRoseTest::SELL_IN;

TEST_F(GildedRoseTest,  NormalItemQualityDecreasesBeforeSellIn) {
    EXPECT_EQ(QUALITY - 1, GetUpdatedItem(Item("Foo", SELL_IN, QUALITY)).quality);
}

TEST_F(GildedRoseTest,  SellInDecreases) {
    EXPECT_EQ(SELL_IN - 1, GetUpdatedItem(Item("Foo", SELL_IN, QUALITY)).sellIn);
}

TEST_F(GildedRoseTest,  NormalItemQualityDecrease2xAfterSellIn) {
    EXPECT_EQ(QUALITY - 2, GetUpdatedItem(Item("Foo", 0, QUALITY)).quality);
}

TEST_F(GildedRoseTest,  ItemQualityNeverNegative) {
    EXPECT_EQ(0, GetUpdatedItem(Item("Foo", SELL_IN, 0)).quality);
}

TEST_F(GildedRoseTest,  ItemQualityNeverNegativeWhenSellInZero) {
    EXPECT_EQ(0, GetUpdatedItem(Item("Foo", 0, 1)).quality);
}

TEST_F(GildedRoseTest,  AgedBrieQualityIncreases) {
    ASSERT_LT(QUALITY, QUALITY_CAP);
    EXPECT_EQ(QUALITY + 1, GetUpdatedItem(Item("Aged Brie", SELL_IN, QUALITY)).quality);
}

TEST_F(GildedRoseTest,  AgedBrieQualityHasCeiling)
{
    EXPECT_EQ(QUALITY_CAP, GetUpdatedItem(Item("Aged Brie", SELL_IN, QUALITY_CAP)).quality);
}

TEST_F(GildedRoseTest,  ExpiredAgedBrieQualityHasCeiling) {
    EXPECT_EQ(QUALITY_CAP, GetUpdatedItem(Item("Aged Brie", 0, QUALITY_CAP - 1)).quality);
    EXPECT_EQ(QUALITY_CAP, GetUpdatedItem(Item("Aged Brie", 0, QUALITY_CAP)).quality);
}

void example()
{
    vector<Item> items;
    items.push_back(Item("+5 Dexterity Vest", 10, 20));
    items.push_back(Item("Aged Brie", 2, 0));
    items.push_back(Item("Elixir of the Mongoose", 5, 7));
    items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    items.push_back(Item("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
    app.updateQuality();
}
