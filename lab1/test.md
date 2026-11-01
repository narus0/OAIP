## 5. Таблица тестов Т1–Т6 и независимые расчёты

### 5.1. Минимальный набор тестов

| ID | Что должен выявить |
| --- | --- |
| Т1 | Демонстрационный: согласованность программы с приведённым эталоном |
| Т2 | Индивидуальный: самостоятельное вычисление ожидаемых значений |
| Т3 | 45 минут: ошибку `duration_minutes / 60` при целочисленном делении |
| Т4 | Дробные проценты: потерю дробной части и неверные скобки |
| Т5 | Один пассажир: `cost_per_passenger` должен совпасть с `trip_cost` |
| Т6 | Контрастный: малый расход при большой дистанции или короткая поездка; разумность единиц |

### 5.2. Таблица тестирования

| ID | Входы | Ожидание | Факт | Итог / объяснение |
| --- | --- | --- | --- | --- |
| Т1 | 120.5 95 64.0 82.0 54.5 0.42 3 | Energy used: 17.60 kWh; Average speed: 76.11 km/h; Consumption: 14.61 kWh/100 km; Trip cost: 7.39 BYN; Cost per passenger: 2.46 BYN | Energy used: 17.60 kWh; Average speed: 76.11 km/h; Consumption: 14.61 kWh/100 km; Trip cost: 7.39 BYN; Cost per passenger: 2.46 BYN | PASS. Значения совпадают с демонстрационным эталоном. |
| Т2 | 140.0 120 64.0 81.0 48.0 0.430 2 | Energy used: 21.12 kWh; Average speed: 70.00 km/h; Consumption: 15.09 kWh/100 km; Trip cost: 9.08 BYN; Cost per passenger: 4.54 BYN | Energy used: 21.12 kWh; Average speed: 70.00 km/h; Consumption: 15.09 kWh/100 km; Trip cost: 9.08 BYN; Cost per passenger: 4.54 BYN | PASS. Значения совпадают с независимым расчётом для варианта 10. |
| Т3 | 60.0 45 50.0 80.0 60.0 0.30 2 | Energy used: 10.00 kWh; Average speed: 80.00 km/h; Consumption: 16.67 kWh/100 km; Trip cost: 3.00 BYN; Cost per passenger: 1.50 BYN | Energy used: 10.00 kWh; Average speed: 80.00 km/h; Consumption: 16.67 kWh/100 km; Trip cost: 3.00 BYN; Cost per passenger: 1.50 BYN | PASS. Если бы использовалось `duration_minutes / 60` без `.0`, `time_hours` стало бы `0`, и средняя скорость была бы неверной. В коде деление корректное. |
| Т4 | 100.0 60 60.0 75.5 50.5 0.40 1 | Energy used: 15.00 kWh; Average speed: 100.00 km/h; Consumption: 15.00 kWh/100 km; Trip cost: 6.00 BYN; Cost per passenger: 6.00 BYN | Energy used: 15.00 kWh; Average speed: 100.00 km/h; Consumption: 15.00 kWh/100 km; Trip cost: 6.00 BYN; Cost per passenger: 6.00 BYN | PASS. Скобки в формуле энергии расставлены верно. Дробные проценты не теряются, так как используются `double` и `%lf`. |
| Т5 | 80.0 50 40.0 90.0 70.0 0.50 1 | Energy used: 8.00 kWh; Average speed: 96.00 km/h; Consumption: 10.00 kWh/100 km; Trip cost: 4.00 BYN; Cost per passenger: 4.00 BYN | Energy used: 8.00 kWh; Average speed: 96.00 km/h; Consumption: 10.00 kWh/100 km; Trip cost: 4.00 BYN; Cost per passenger: 4.00 BYN | PASS. При одном пассажире `cost_per_passenger_byn` совпадает с `trip_cost_byn`. |
| Т6 | 500.0 30 100.0 100.0 90.0 0.20 4 | Energy used: 10.00 kWh; Average speed: 1000.00 km/h; Consumption: 2.00 kWh/100 km; Trip cost: 2.00 BYN; Cost per passenger: 0.50 BYN | Energy used: 10.00 kWh; Average speed: 1000.00 km/h; Consumption: 2.00 kWh/100 km; Trip cost: 2.00 BYN; Cost per passenger: 0.50 BYN | PASS. Малая длительность при большой дистанции даёт очень высокую среднюю скорость; малый расход энергии при большой дистанции даёт низкий расход на 100 км. Единицы остаются разумными. |

### 5.3. Независимые расчёты

#### Т1 - демонстрационный набор

**Вход:**

| Параметр | Значение |
| --- | --- |
| `distance_km` | 120.5 |
| `duration_minutes` | 95 |
| `battery_capacity_kwh` | 64.0 |
| `start_charge_percent` | 82.0 |
| `finish_charge_percent` | 54.5 |
| `tariff_byn_per_kwh` | 0.42 |
| `passengers` | 3 |

**Промежуточные вычисления:**

| Величина | Расчёт | Значение |
| --- | --- | --- |
| `time_hours` | 95 / 60.0 | 1.583333... |
| `energy_used_kwh` | 64.0 * (82.0 - 54.5) / 100.0 | 17.6000 |
| `average_speed_kwh` | 120.5 / 1.583333... | 76.1052... |
| `consumption_kwh_per_100km` | 17.6000 / 120.5 * 100.0 | 14.6058... |
| `trip_cost_byn` | 17.6000 * 0.42 | 7.3920 |
| `cost_per_passenger_byn` | 7.3920 / 3 | 2.4640 |

**Ожидаемые строки отчёта:**

| Показатель | Значение |
| --- | --- |
| Energy used | 17.60 kWh |
| Average speed | 76.11 km/h |
| Consumption | 14.61 kWh/100 km |
| Trip cost | 7.39 BYN |
| Cost per passenger | 2.46 BYN |

#### Т2 - индивидуальный набор (вариант V = 10)

**Вход:**

| Параметр | Значение |
| --- | --- |
| `distance_km` | 140.0 |
| `duration_minutes` | 120 |
| `battery_capacity_kwh` | 64.0 |
| `start_charge_percent` | 81.0 |
| `finish_charge_percent` | 48.0 |
| `tariff_byn_per_kwh` | 0.430 |
| `passengers` | 2 |

**Промежуточные вычисления:**

| Величина | Расчёт | Значение |
| --- | --- | --- |
| `time_hours` | 120 / 60.0 | 2.000000 |
| `energy_used_kwh` | 64.0 * (81.0 - 48.0) / 100.0 | 21.1200 |
| `average_speed_kwh` | 140.0 / 2.000000 | 70.0000 |
| `consumption_kwh_per_100km` | 21.1200 / 140.0 * 100.0 | 15.0857... |
| `trip_cost_byn` | 21.1200 * 0.430 | 9.0816 |
| `cost_per_passenger_byn` | 9.0816 / 2 | 4.5408 |

**Ожидаемые строки отчёта:**

| Показатель | Значение |
| --- | --- |
| Energy used | 21.12 kWh |
| Average speed | 70.00 km/h |
| Consumption | 15.09 kWh/100 km |
| Trip cost | 9.08 BYN |
| Cost per passenger | 4.54 BYN |

#### Т3 - 45 минут

**Вход:**

| Параметр | Значение |
| --- | --- |
| `distance_km` | 60.0 |
| `duration_minutes` | 45 |
| `battery_capacity_kwh` | 50.0 |
| `start_charge_percent` | 80.0 |
| `finish_charge_percent` | 60.0 |
| `tariff_byn_per_kwh` | 0.30 |
| `passengers` | 2 |

**Промежуточные вычисления:**

| Величина | Расчёт | Значение |
| --- | --- | --- |
| `time_hours` | 45 / 60.0 | 0.750000 |
| `energy_used_kwh` | 50.0 * (80.0 - 60.0) / 100.0 | 10.0000 |
| `average_speed_kwh` | 60.0 / 0.750000 | 80.0000 |
| `consumption_kwh_per_100km` | 10.0000 / 60.0 * 100.0 | 16.6667 |
| `trip_cost_byn` | 10.0000 * 0.30 | 3.0000 |
| `cost_per_passenger_byn` | 3.0000 / 2 | 1.5000 |

Если использовать `duration_minutes / 60` без `.0`, получится `time_hours = 0`, что приведёт к делению на ноль и неверной средней скорости.

#### Т4 - дробные проценты

**Вход:**

| Параметр | Значение |
| --- | --- |
| `distance_km` | 100.0 |
| `duration_minutes` | 60 |
| `battery_capacity_kwh` | 60.0 |
| `start_charge_percent` | 75.5 |
| `finish_charge_percent` | 50.5 |
| `tariff_byn_per_kwh` | 0.40 |
| `passengers` | 1 |

**Промежуточные вычисления:**

| Величина | Расчёт | Значение |
| --- | --- | --- |
| `time_hours` | 60 / 60.0 | 1.000000 |
| `energy_used_kwh` | 60.0 * (75.5 - 50.5) / 100.0 | 15.0000 |
| `average_speed_kwh` | 100.0 / 1.000000 | 100.0000 |
| `consumption_kwh_per_100km` | 15.0000 / 100.0 * 100.0 | 15.0000 |
| `trip_cost_byn` | 15.0000 * 0.40 | 6.0000 |
| `cost_per_passenger_byn` | 6.0000 / 1 | 6.0000 |

Если потерять дробную часть (`75` и `50` вместо `75.5` и `50.5`), `energy_used_kwh` изменится, и расхождение будет заметно на других наборах. Если перепутать скобки, получится `60.0 * 75.5 - 50.5 / 100.0 = 4529.495`, что явно неверно.

#### Т5 - один пассажир

**Вход:**

| Параметр | Значение |
| --- | --- |
| `distance_km` | 80.0 |
| `duration_minutes` | 50 |
| `battery_capacity_kwh` | 40.0 |
| `start_charge_percent` | 90.0 |
| `finish_charge_percent` | 70.0 |
| `tariff_byn_per_kwh` | 0.50 |
| `passengers` | 1 |

**Промежуточные вычисления:**

| Величина | Расчёт | Значение |
| --- | --- | --- |
| `time_hours` | 50 / 60.0 | 0.833333... |
| `energy_used_kwh` | 40.0 * (90.0 - 70.0) / 100.0 | 8.0000 |
| `average_speed_kwh` | 80.0 / 0.833333... | 96.0000 |
| `consumption_kwh_per_100km` | 8.0000 / 80.0 * 100.0 | 10.0000 |
| `trip_cost_byn` | 8.0000 * 0.50 | 4.0000 |
| `cost_per_passenger_byn` | 4.0000 / 1 | 4.0000 |

При одном пассажире `cost_per_passenger_byn` должна совпасть с `trip_cost_byn`.

#### Т6 - контрастный

**Вход:**

| Параметр | Значение |
| --- | --- |
| `distance_km` | 500.0 |
| `duration_minutes` | 30 |
| `battery_capacity_kwh` | 100.0 |
| `start_charge_percent` | 100.0 |
| `finish_charge_percent` | 90.0 |
| `tariff_byn_per_kwh` | 0.20 |
| `passengers` | 4 |

**Промежуточные вычисления:**

| Величина | Расчёт | Значение |
| --- | --- | --- |
| `time_hours` | 30 / 60.0 | 0.500000 |
| `energy_used_kwh` | 100.0 * (100.0 - 90.0) / 100.0 | 10.0000 |
| `average_speed_kwh` | 500.0 / 0.500000 | 1000.0000 |
| `consumption_kwh_per_100km` | 10.0000 / 500.0 * 100.0 | 2.0000 |
| `trip_cost_byn` | 10.0000 * 0.20 | 2.0000 |
| `cost_per_passenger_byn` | 2.0000 / 4 | 0.5000 |

Малая длительность при большой дистанции даёт очень высокую среднюю скорость; малый расход энергии при большой дистанции даёт низкий расход на 100 км. Единицы должны оставаться разумными.
