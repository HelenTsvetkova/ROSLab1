# ROSLab1
Сборку можно провести с помощью catkin. Переходим в директорию с исходниками и инициализируем воркспейс:

`cd src`

`catkin_init_workspace`

Потом собираем:

`cd ..`

`catkin_make`

---

Чтобы запустить ноду необходимо запустить launch файл:

`roslaunch dino_generator dino_generator.launch`

Чтобы отправить запрос сервису (ноде) нужно:

`rosservice call /generate_dino_name` + TAB и заполнить поле word

Чтобы посмотреть, что пришло в топик:

`rostopic echo /dino_species`

Чтобы поменять название топика, необходимо поменять параметр в launch файле:

`<param name="topic_name" value="dino_species"/>`
