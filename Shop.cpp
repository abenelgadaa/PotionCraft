
#include "Shop.h"
#include <string>

using namespace std;

Shop::Shop()
{
    m_shopName = "Test";
    m_numIngredients = 0;
    m_shopRank = 'F';
}

Shop::Shop(string name)
{
    m_shopName = name;
    m_numIngredients = 0;
    m_shopRank = 'F';
}

string Shop::GetName()
{
    return m_shopName;
}

void Shop::SetName(string name)
{
    m_shopName = name;
}

int Shop::CheckIngredient(Ingredient ingredient)
{
    for (int i = 0; i < m_numIngredients; i++)
    {
        if (m_myIngredients[i].m_name.compare(ingredient.m_name) == 0)
            return i;
    }
    return -1;
}

void Shop::AddIngredient(Ingredient ingredient)
{
    if (m_numIngredients < PROJ2_SIZE)
    {
        m_myIngredients[m_numIngredients] = ingredient;
        m_numIngredients++;
    }
}

void Shop::IncrementQuantity(Ingredient ingredient)
{
    int ingredient_index = CheckIngredient(ingredient);
    if (ingredient_index != -1)
    {
        m_myIngredients[ingredient_index].m_quantity ++;
    }
}

bool Shop::DecrementQuantity(Ingredient ingredient)
{
    int ingredient_index = CheckIngredient(ingredient);
    if (ingredient_index != -1)
    {
        if (m_myIngredients[ingredient_index].m_quantity > 0)
        {
            m_myIngredients[ingredient_index].m_quantity --;
            return true;
        }
    }
    return false;
}

bool Shop::CheckQuantity(Ingredient ingredient1, Ingredient ingredient2)
{
    if (ingredient1.m_name.compare(ingredient2.m_name) == 0)
    {
        int ingredient_index = CheckIngredient(ingredient1);
        if (ingredient_index != -1)
        {
            int ingredient_quantity = m_myIngredients[ingredient_index].m_quantity;
            if (ingredient_quantity >= 2)
                return true;
        }
    }
    else
    {
        int ingredient1_index = CheckIngredient(ingredient1);
        int ingredient2_index = CheckIngredient(ingredient2);
        if (ingredient1_index != -1 && ingredient2_index != -1)
        {
            int ingredient1_quantity = m_myIngredients[ingredient1_index].m_quantity;
            int ingredient2_quantity = m_myIngredients[ingredient2_index].m_quantity;
            if (ingredient1_quantity > 0 && ingredient2_quantity > 0)
                return true;
        }
    }
    return false;
}

Ingredient Shop::GetIngredient(int index)
{
    return m_myIngredients[index];
}

void Shop::CalcRank()
{
    int current_count = IngredientCount();
    float rank = ((float)current_count/(float)m_numIngredients)*100.f;
    if (rank < RANK_D) m_shopRank = 'F';
    if (rank >= RANK_D && rank < RANK_C) m_shopRank = 'D';
    if (rank >= RANK_C && rank < RANK_B) m_shopRank = 'C';
    if (rank >= RANK_B && rank < RANK_A) m_shopRank = 'B';
    if (rank >= RANK_A && rank < RANK_S) m_shopRank = 'A';
    if (rank >= RANK_S) m_shopRank = 'S';
}

char Shop::GetRank()
{
    return m_shopRank;
}

int Shop::IngredientCount()
{
    int count = 0;
    for (int i = 0; i < m_numIngredients; i++)
    {
        if (m_myIngredients[i].m_quantity > 0)
            count ++;
    }
    return count;
}

void Shop::ShopScore()
{
    cout << endl << endl;
    cout << "*** The Potion Shop***" << endl << endl;
    cout << "Owned by: " << m_shopName << endl << endl;
    cout << "There are " << m_numIngredients << " available products." << endl << endl;
    int current_ingredient_count = IngredientCount();
    cout << "This shop has " << current_ingredient_count << " products in stock." << endl << endl;
    float percentage = ((float) current_ingredient_count / (float) m_numIngredients)*100.f;
    cout << "Which is " << percentage << "%" << endl << endl;
    CalcRank();
    char rank = GetRank();
    cout << "Shop Rank: " << rank << endl << endl;
}