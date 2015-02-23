#include "GildedRose.h"

char const * const GildedRose::AGED_BRIE_NAME = "Aged Brie";
char const * const GildedRose::SULFURAS_NAME = "Sulfuras, Hand of Ragnaros";
char const * const GildedRose::BACKSTAGE_PASSES_NAME = "Backstage passes to a TAFKAL80ETC concert";


GildedRose::GildedRose(vector<Item> & items) : items(items)
{}

void GildedRose::updateQuality() 
{
    for (int i = 0; i < items.size(); i++)
    {
       if (items[i].name != AGED_BRIE_NAME && items[i].name != BACKSTAGE_PASSES_NAME)
        {
            if (items[i].quality > 0)
            {
                if (items[i].name != SULFURAS_NAME)
                {
                    items[i].quality = items[i].quality - 1;
                }
            }
        }
        else
        {
            if (items[i].quality < 50)
            {
                items[i].quality = items[i].quality + 1;

                if (items[i].name == BACKSTAGE_PASSES_NAME)
                {
                    if (items[i].sellIn < 11)
                    {
                        if (items[i].quality < 50)
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }

                    if (items[i].sellIn < 6)
                    {
                        if (items[i].quality < 50)
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }
                }
            }
        }

        if (items[i].name != SULFURAS_NAME)
        {
            items[i].sellIn = items[i].sellIn - 1;
        }

        if (items[i].sellIn < 0)
        {
            if (items[i].name != AGED_BRIE_NAME)
            {
                if (items[i].name != BACKSTAGE_PASSES_NAME)
                {
                    if (items[i].quality > 0)
                    {
                        if (items[i].name != SULFURAS_NAME)
                        {
                            items[i].quality = items[i].quality - 1;
                        }
                    }
                }
                else
                {
                    items[i].quality = items[i].quality - items[i].quality;
                }
            }
            else
            {
                if (items[i].quality < 50)
                {
                    items[i].quality = items[i].quality + 1;
                }
            }
        }
    }
}

GildedRose::ItemType GildedRose::GetItemType(const Item &item)
{
    if(item.name == AGED_BRIE_NAME) {
        return CHEESE;
    } else if(item.name == BACKSTAGE_PASSES_NAME) {
        return BACKSTAGE_PASS;
    } else if(item.name == SULFURAS_NAME) {
        return LEGENDARY;
    } else {
        return NORMAL;
    }
}

void PassItem::updateQuality()
{
if (m_item.sellIn > 10)
}

void PassItem::updateSellin()
{

}
