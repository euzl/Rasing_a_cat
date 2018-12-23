
# Rasing_a_cat
**[Linux]**  고양이 키우기 초미니게임 
I'm the only one who doesn't have a cat.  

## 고양이 기르기 게임 (Mini Game of Rasing a cat)   
### '나만 고양이 없어...'  (I'm the only one who doesn't have a cat.)    
현대인들은 고양이들을 귀여워한다. 모두 고양이를 키우고 싶어하지만 고양이가 없어서 고양이의 사진이나 동영상을 보며 대리만족하는 사람들이 많다. 이들을 위해 고양이와 교감할 수 있는 초미니게임 ~~(이라고 말하기도 민망한)~~ 을 만들었다.

### 구성 (Configuration)
Cat(Server) ↔ Butler(Client)
Using UDP protocol

**Cat**  
고양이. 서버의 역할을 한다. 이름을 입력 받고, 사용자가 한 행위를 출력해준다. 교감할수록 Close(친밀감)이 높아지고, 친밀감이 15가 될 때마다 Level이 하나씩 올라간다. 교감할 때마다 Purr..(골골송)거린다.

**Butler**  
집사. 클라이언트의 역할을 한다. 제일 먼저 고양이의 이름을 지어주며 분양 받는다. 시작하면 교감할 수 있는 목록이 뜨는데, 번호를 입력하면 Cat으로 전송된다. 

※ ‘0’을 입력하면 종료됨

## 작동 방법 (How to Play)
우선 컴파일 해준다.

    $gcc -o cat cat.c
    $gcc -o butler butler.c

cat과 butler를 동시에 실행시켜준다.

    $./cat
    I'm the only one who doesn't have a cat.
    Wait for adoption...
    [Navi] Close: 0   Level : 1
    I fed the cat.
    [Navi] Close: 5   Level : 1
    I had a high five with the cat.
    [Navi] Close: 8   Level : 1
    --The End--
    My Level is 1


    $./butler
    Set Cat's Name>Navi
    1. Hand (+2)
    2. High five (+3)
    3. Feed (+5)
    4. Play (+4)
    5. Pat (+5)
    6. Snack (+7)
    7. Exit (Shut down)
    [!!]I have adopted a cat.
    Do> 3
    [Navi]Pur Purr
    Do> 2
    [Navi]Purr.
    Do> 0
    $
    
1. [butler]Name을 입력한다. (ex. Navi)
2. [butler]목록에서 교감할 행위의 번호를 입력한다. (ex. 3)
3. [cat]사용자가 한 교감행위를 출력한다.
4. [cat]업데이트된 Close와 Level을 보여준다.
5. [cat]Purr(골골송)을 butler에게 보낸다.
6. [butler]Purr가 출력된다.
7. 2-6을 반복한다.
8. '0'을 입력하면 종료한다.
