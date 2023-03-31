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
