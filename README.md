# SFML_STUDY
1. sfml_hello.zip 압축을 푼다
2. 압축 푼 디렉토리에 mkdir build 로 디렉토리를 생성한다.
3. cd build
4. cmake ..
(cmake 설치되어 있지 않으면 해당 사이트에 가서 다운받아 설치함)
5. cmake --build .
(정상적으로 컴파일 되면 Debug 디렉토리에 sfml_hello2.exe 파일이 생성됨)
6. 실행파일 디렉토리에 sfml 관련 dll 파일들 및 폰트 파일이 있어야 함
(sfml 관련 dll 파일은 sfml 사이트에서 다운받은 파일의 bin 디렉토리에 있으며, font 파일은 검색하면 OS 설치 디렉토리에 보통 존재함)

7.dll파일은 위에 올려져있는 bin파일을 사용하세요. 공식사이트에서 다운받은 bin파일에 있는 dll파일은 갯수가 부족했던걸로 압니다.

8.실행파일에 bin파일을 넣은 후, 환경설정에서 path를 설정해주시면 SFML을 사용할 세팅은 완료되었습니다.
    
## 주의사항

특정 상황에서는 위와 같은 과정을 거쳐도 IDE에서 컴파일을 할 수 없는 경우가 발생합니다.
이 경우 다음과 같은 과정을 따라 주세요.

1. 위에 있는 SFML파일을 다운받거나 공식 사이트에서 다운받아서 특정 경로에 저장을 합니다.(ex: C/SFML)
2. SFML 아래 bin파일의 경로를 환경변수로 설정합니다.
3. IDE(CLions, VSC, ...)에서 컴파일 하고 싶은 프로젝트를 실행합니다.
4. 터미널을 실행한 뒤, 다음 명령어를 실행합니다.
 - g++ -c {실행할 cpp파일 전부} -I{SFML의 includ파일 경로} (예: g++ -c shape_main.cpp shape.cpp -IC:/SFML/include)
 - g++ {생성된 object파일 전부} -L{SFML의 lib 파일 경로 } -lsfml-window -lsfml-graphics -lsfml-system
 (예: g++ shape_main.o shape.o -LC:/SFML/lib -lsfml-window -lsfml-graphics -lsfml-system)

5.위 명령을 실행하면, 실행할 cpp파일이 있는 위치에 생성된 object파일과, 생성된 실행파일 a.exe이 존재할 것입니다.
이때 a.exe를 클릭해서 실행하면 프로젝를 실행 시킬수 있습니다.
