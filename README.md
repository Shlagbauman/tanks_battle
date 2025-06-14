# Tanks 2D

SFML-аркада для двух игроков: уничтожь соперника, собирай бонусы ⭐ 🛡 и набирай очки.

| Игрок   | Движение | Огонь | Прочее |
|---------|----------|-------|--------|
| Зелёный | W A S D  | Space |        |
| Красный | ⬆ ⬅ ⬇ ➡| R-Ctrl / L-Ctrl / Enter | |
| Оба | | | **F1** – сменить карту |

* **Speed** ⭐ — &times;1,5 скорости на 5 с (макс 240 px/с)  
* **Shield** 🛡 — неуязвимость 3 с (синее кольцо R&asymp;120 px)

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/tanks2d.exe