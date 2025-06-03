/*
Ce fichier sert à fournir des versions factices (stubs) des fonctions du HAL,
afin que le linker puisse résoudre ces symboles lors de la compilation
des tests sans avoir besoin du code réel du HAL.
Cela permet de tester les module du kernel isolément, sans dépendance matérielle.
*/

void systick_register_hook(void (*hook)(void))
{
}

void systick_init(void)
{
}
