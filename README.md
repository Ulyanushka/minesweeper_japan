План: Сапёр, где при ошибке даётся второй шанс, если правильно ответишь на карточку с вопросом.

План на следующую итерацию: добавить в настройщик количество ответов на квиз а) необходимых для победы (дефолт - 1) и б) в принципе доступных ответов (дефолт - 8), также добавить выбор базы или даже несколько баз одновременно, такжедобавить возможность просто так играть в квиз, отдельно от сапёра, также добавить вариан добавления новых баз (их нужно будет сделать в json по шаблону

---------------------------------------------------------------------------------------------------

v0.4
1) Теперь при открытии мины предлагается пройти квиз
2) Сейчас квиз составляется на основе только одной базы данных, там всегда восемь ответов (один из них правильный)
3) Пока квиз активен, поле сапёра заблокировано, а из самого квиза выйти нельзя, пока не ответишь на хотя бы один вопрос
4) Если ответишь правильно, можешь продолжить игру (открытая мина будет скрыта и помечена флажком)
5) Или можно продолжить отвечать на квиз (но если один раз ответил правильно, то в дальнейшем можно в любой момент вернуться в игру)
6) Если ответишь неправильно, можно начать игру заново или продолжить отвечать на квиз (как только ответишь правильно - сможешь продолжить игру)
   
![image](https://github.com/user-attachments/assets/00c08ab8-775c-4400-96a0-84253fa8512e)
![image](https://github.com/user-attachments/assets/655306e5-5b3e-4168-81ab-1932497dcba9)

![image](https://github.com/user-attachments/assets/20152554-a65c-468f-b084-139c1b5a8f71)
![image](https://github.com/user-attachments/assets/2dbb1c57-b96c-4f04-b55c-cacd3e230ea0)
![image](https://github.com/user-attachments/assets/5cdecc9b-3a08-4dc9-b9f7-625cc74b4bc0)

---------------------------------------------------------------------------------------------------

v0.3
1) теперь на основном экране выводится информация о помеченных минах, количестве сделанных ошибок и кликов (считаются только "полезные" клики, которые что-то на поле меняют, а, например, клик на уже открытую клетку ничего не меняет и засчитываться не будет)
2) если открыл мину, получаешь всплывающее окно "GameOver", где можно либо начать новую игру (с теми же настройками), либо нажать "Sorry", так что игра продолжится, мина будет скрыта за флажком, а счётчик ошибок увеличится.
3) теперь можно победить (все клетки поля должны быть либо открыты, либо помечены флажком, а количество флажков должно совпадать с количеством мин)
4) добавилась возможность настроить поле (ширина и высота, 1-30 клеток, а также количество мин, которое не должно превышать количество клеток на поле)

![image](https://github.com/user-attachments/assets/f4e4ff5f-212b-4480-ac22-a129b669309e)
![image](https://github.com/user-attachments/assets/dad58bf7-79d8-45ea-9d38-6e5775047555)
![image](https://github.com/user-attachments/assets/70d90f3f-803c-411e-ae0f-526f7233a6b1)
![image](https://github.com/user-attachments/assets/df4b6812-a62c-4746-8bcb-a65ec061868f)

---------------------------------------------------------------------------------------------------

v0.2 - добавила проигрыш при открытии мины, возможность начать заново, вывела информацию о помеченных минах и их общем количестве, а также общую информацию о поле: ряды, колонки, количество клеток и мин, процент мин от общего количества клеток

![image](https://github.com/user-attachments/assets/f197b059-f115-46d4-94e6-a2c4658bb2f7)

---------------------------------------------------------------------------------------------------

v0.1 - добавила цвета для мин и каунтеров, теперь можно ставить по клику на левую кнопку мышки "флажки" предполагаемых мин, ешё пустые области открываются при клике на пустую клетку. 

![image](https://github.com/user-attachments/assets/6a5e7825-7a6e-453a-affc-f64fde7e0fb7)

---------------------------------------------------------------------------------------------------

v0.0 - строится скрытое сапёрное поле: мины, каунтеры мин - которое можно открывать, кликая на клетки

![image](https://github.com/user-attachments/assets/d803a371-96a8-426c-8c9e-5c6ea4556b05)
