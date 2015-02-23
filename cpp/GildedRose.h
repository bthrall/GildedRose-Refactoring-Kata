#include <string>
#include <vector>

using namespace std;

class Item
{
public:
    string name;
    int sellIn;
    int quality;

    Item(string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}
};

class UpdateableItem {
public:
    virtual void updateQuality() = 0;
    virtual void updateSellin() = 0;
private:
    Item &m_item;
};

class NormalItem : public UpdateableItem {

};

class PassItem : public UpdateableItem
{
public:

    virtual void updateQuality();

    virtual void updateSellin();
};

class GildedRose
{
public:
    vector<Item> & items;
    GildedRose(vector<Item> & items);
    
    void updateQuality();
    static char const * const AGED_BRIE_NAME;
    static char const * const SULFURAS_NAME;
    static char const * const BACKSTAGE_PASSES_NAME;

    enum ItemType {
        CHEESE,
        LEGENDARY,
        BACKSTAGE_PASS,
        CONJURED,
        NORMAL
    };

    ItemType GetItemType(const Item &item);
};

