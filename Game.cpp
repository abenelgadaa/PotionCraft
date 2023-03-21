#include "Game.h"

using namespace std;

Game::Game(){
    cout << "Game started..." << endl << endl;
}

void Game::LoadIngredients()
{
    fstream new_file;
    new_file.open(PROJ2_DATA, ios::in);
    int count = 0;
    if (new_file.is_open())
    {
        string ingredient_name;
        string ingredient_type;
        string ingredient1;
        string ingredient2;
        while(getline(new_file, ingredient_name, ','))
        {
            getline(new_file, ingredient_type, ',');
            getline(new_file, ingredient1, ',');
            getline(new_file, ingredient2);
            Ingredient ingredient(ingredient_name, ingredient_type, ingredient1, ingredient2, 0);
            m_ingredients[count] = ingredient;
            m_myShop.AddIngredient(ingredient);
            count ++;
        }
        cout << endl << PROJ2_SIZE << " ingredients loaded." << endl << endl;
    }
    else cout << "could not open file " << endl;
}

void Game::StartGame()
{
    GameTitle();
    LoadIngredients();
    string shop_name = "Test";
    cout << "What is the name of your Shop?" << endl << endl;
    getline (cin, shop_name);
    cout << endl;
    m_myShop.SetName(shop_name);
    int choice = 0;
    do{
        choice = MainMenu();
        if (choice == 1) DisplayIngredients();
        if (choice == 2) SearchIngredients();
        if (choice == 3) CombineIngredients();
        if (choice == 4) m_myShop.ShopScore();
    }while(choice != 5);
    cout << "Thanks for playing UMBC Potion Craft**5-61 removed for space**" << endl << endl;
}



void Game::DisplayIngredients()
{
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        Ingredient ingredient = m_myShop.GetIngredient(i);
        cout << i+1 << ". " << ingredient.m_name << " " << ingredient.m_quantity << endl << endl;
    }
}

int Game::MainMenu()
{
    int choice = 0;
    char rank = 'F';
    do{
        m_myShop.CalcRank();
        rank = m_myShop.GetRank();
        if (rank == 'S')
        {
            choice = 5;
            cout << "You won the game, you have reached S rank !" << endl << endl;
            break;
        }
        cout << "What would you like to do in " << m_myShop.GetName() << " shop?" << endl << endl;
        cout << "1. Display your Shop's Ingredients" << endl << endl;
        cout << "2. Search for Natural Ingredients" << endl << endl;
        cout << "3. Attempt to Merge Ingredients" << endl << endl;
        cout << "4. See Score" << endl << endl;
        cout << "5. Quit" << endl << endl;
        cin >> choice;
        cout << endl;

    }while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
    return choice;
}

void Game::SearchIngredients()
{
    int random_index = rand() % PROJ2_SIZE;
    Ingredient ingredient;
    do{
        ingredient = m_ingredients[random_index];
        random_index = rand() % PROJ2_SIZE;
    }while(ingredient.m_type.compare("natural") != 0);
    m_myShop.IncrementQuantity(ingredient);
    cout << ingredient.m_name << " Found!" << endl << endl;
}

void Game::CombineIngredients()
{
    int choice1 = 0;
    int choice2 = 0;
    RequestIngredient(choice1);
    RequestIngredient(choice2);
    choice1--;
    choice2--;
    Ingredient ingredient1 = m_myShop.GetIngredient(choice1);
    Ingredient ingredient2 = m_myShop.GetIngredient(choice2);
    int index_recipe_found = SearchRecipes(ingredient1.m_name, ingredient2.m_name);
    if (index_recipe_found == -1)
    {
        cout << "There is no recipe with the chosen ingredients..."<< endl << endl;
    }
    else
    {
        if (m_myShop.CheckQuantity(ingredient1, ingredient2))
        {
            Ingredient new_ingredient = m_ingredients[index_recipe_found];
            cout << ingredient1.m_name << " combined with " << ingredient2.m_name << " to make " << new_ingredient.m_name << "!" << endl << endl;
            cout << "You have made " << new_ingredient.m_name << " for your shop." << endl << endl;
            m_myShop.IncrementQuantity(new_ingredient);
            m_myShop.DecrementQuantity(ingredient1);
            m_myShop.DecrementQuantity(ingredient2);
        }
        else
        {
            cout << "You do not have enough " << ingredient1.m_name << " or " << ingredient2.m_name << " to attempt that merge" << endl << endl;
        }
    }
}

void Game::RequestIngredient(int &choice)
{
    do{
        cout << "What ingredients would you like to merge?" << endl << endl;
        cout << "To list known ingredients enter -1" << endl << endl;
        cin >> choice;
        cout << endl;
        if (choice == -1)
            DisplayIngredients();
    }while (choice > PROJ2_SIZE || choice <1);
}

int Game::SearchRecipes(string ingredient1_name, string ingredient2_name)
{
    for (int i = 0; i < PROJ2_SIZE; i++){
        Ingredient ingredient = m_ingredients[i];
        if ((ingredient.m_ingredient1.compare(ingredient1_name) == 0 && ingredient.m_ingredient2.compare(ingredient2_name) == 0) || 
            (ingredient.m_ingredient1.compare(ingredient2_name) == 0 && ingredient.m_ingredient2.compare(ingredient1_name) == 0)   )
        {
            return i;
        }
    }
    return -1;
    
}