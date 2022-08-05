## Part 1. Готовый докер

- Взять официальный докер образ с nginx и выкачать его при помощи `docker pull`  
	![](image/P1/nginx_pull.PNG)

- Проверить наличие докер образа через `docker images`  
	![](image/P1/docker_images.PNG)

- Запустить докер образ через `docker run -d [image_id|repository]`  
	![](image/P1/docker_run.PNG)

- Проверить, что образ запустился через `docker ps`  
	![](image/P1/docker_ps.PNG)
- Посмотреть информацию о контейнере через `docker inspect 
[container_id|container_name]`. По выводу команды определить и поместить в отчёт:  
	* размер контейнера: _Size: 141505630 B_
	* список замапленных портов: _Ports: 80/tcp: null_
	* ip контейнера: _IPAddress: 172.17.0.2_  

-  Остановить докер образ через `docker stop [container_id|container_name]`  
![](image/P1/docker_stop.PNG)

- Проверить, что образ остановился через `docker ps`  
![](image/P1/docker_ps2.PNG)

- Запустить докер с замапленными портами __80__ и __443__ на локальную машину через команду `run`  
![](image/P1/docker_run_80_443.PNG)

- Проверить, что в браузере по адресу _localhost:80_ доступна стартовая страница _nginx_  
![](image/P1/nginx_web.PNG)

- Перезапустить докер образ через `docker restart [image_id|repository]`  
![](image/P1/docker_restart.PNG)

- Проверить любым способом, что контейнер запустился  
![](image/P1/docker_ps3.PNG)

## Part 2. Операции с контейнером

- Прочитать конфигурационный файл _nginx.conf_ внутри докер образа через команду `exec`  
![](image/P2/ngixconf_orig.PNG)

- Создать на локальной машине файл _nginx.conf_.  
Настроить в нем по пути _/status_ отдачу страницы статуса сервера nginx  
![](image/P2/nginxconf_new.PNG)

- Скопировать созданный файл _nginx.conf_ внутрь докер образа через команду `docker cp`  
![](image/P2/nginxconf_copy.PNG)

- Перезапустить nginx внутри докер образа через команду `exec`  
![](image/P2/nginx_reload.PNG)

- Проверить, что по адресу _localhost:80/status_ отдается страничка со статусом сервера nginx  
![](image/P2/nginx_status.PNG)

- Экспортировать контейнер в файл _container.tar_ через команду `export`  
![](image/P2/docker_export.PNG)

- Остановить контейнер  
![](image/P2/docker_stop.PNG)

- Удалить образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры  
![](image/P2/docker_rmi.PNG)

- Импортировать контейнер обратно через команду `import`  
![](image/P2/docker_import.PNG)

- Запустить импортированный контейнер  
![](image/P2/docker_run.PNG)

## Part 3. Мини веб-сервер

- Написать мини сервер на _C_ и _FastCgi_, который будет возвращать простейшую страничку с надписью _Hello World!_  
![](image/P3/minisrv.PNG)

- Написать свой _nginx.conf_, который будет проксировать все - запросы с __81__ порта на __127.0.0.1:8080__  
![](image/P3/ngixconf.PNG)

- Положить файл _nginx.conf_ по пути _./nginx/nginx.conf_, также копируем _minisrv.c_  
![](image/P3/copy.PNG)

- Запустить написанный мини сервер через `spawn-cgi` на порту __8080__  
![](image/P3/minisrv_start.PNG)

- Проверить, что в браузере по __localhost:81__ отдается написанная вами страничка
![](image/P3/lynx_81.PNG)

## Part 4. Свой докер

- Написать свой докер образ, который:
1) собирает исходники мини сервера на FastCgi из Части 3
2) запускает его на 8080 порту
3) копирует внутрь образа написанный ./nginx/nginx.conf
4) запускает nginx.
nginx можно установить внутрь докера самостоятельно, а можно воспользоваться готовым образом с nginx'ом, как базовым.
Dockerfile:  
![](image/P4/dockerfile.PNG)

- Собрать написанный докер образ через docker build при этом указав имя и тег  
![](image/P4/build.png)

- Проверить через docker images, что все собралось корректно  
![](image/P4/docker_images.PNG)

- Запустить собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а (см. Часть 2)  
![](image/P4/docker_run.PNG)

- Проверить, что по localhost:80 доступна страничка написанного мини сервера  
![](image/P4/localhost80.PNG)

- Дописать в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx  
![](image/P4/ngix_status.PNG)


- Перезапустить докер образ. Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер образа должен обновиться самостоятельно без лишних действий. Проверить, что теперь по localhost:80/status отдается страничка со статусом nginx  
![](image/P4/localhost80status.PNG)

## Part 5. Dockle
- Установка dockle на Ubuntu:  
`VERSION=$(curl --silent "https://api.github.com/repos/goodwithtech/dockle/releases/latest" | grep '"tag_name":' | sed -E 's/.*"v([^"]+)".*/\1/') && curl -L -o dockle.deb https://github.com/goodwithtech/dockle/releases/download/v${VERSION}/dockle_${VERSION}_Linux-64bit.deb`  
$ `sudo dpkg -i dockle.deb && rm dockle.deb`

- Просканировать контейнер из предыдущего задания через `dockle [container_id|container_name]`  
![](image/P5/dockle1.PNG)

- Исправить контейнер так, чтобы при проверке через dockle не было ошибок и предупреждений  
![](image/P5/dockle2.PNG)

## Part 6. Базовый Docker Compose

- Написать файл docker-compose.yml:  
![](image/P6/yml.PNG)

- Собрать и запустить проект с помощью команд docker-compose build и docker-compose up  
![](image/P6/docker-compose-up.PNG)

- Проверить, что в браузере по localhost:80 отдается написанная вами страничка, как и ранее  
![](image/P6/localhost80.PNG)
