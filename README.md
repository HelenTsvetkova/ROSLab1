# ROSLab1
Сборку можно провести с помощью catkin. Переходим в директорию с исходниками и инициализируем воркспейс:
`cd dinoWorkspace/src`
`catkin_init_workspace`
Потом собираем:
`cd dinoWorkspace`
`catkin_make`

---

Чтобы запустить ноду необходимо эмулировать среду:
`roscore`
Запустить ноду:
`rosrun dinogenerator dinoserver`
Чтобы отправить запрос сервису (ноде) нужно:
`rosservice call /generate_dino_name` + TAB и заполнить поле word
Чтобы посмотреть, что пришло в топик:
`rostopic echo /DinoSpecies`
