#include <iostream>
#include <fstream>
using namespace std;

class Helper;
class Object;
class Date;
class Page;
class User;
class Post;
class Comment;
class Social;

class Helper
{
public:
	static int strlen(const char* str)
	{
		int size = 0;
		for (int i = 0; str[i] != '\0'; i++)
			size++;
		return size;
	}
	static void strCopy(char* dest, const char* src)
	{
		int i;
		for (i = 0; src[i] != '\0'; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';
	}
	static bool checkString(char* str1, const char* str2)
	{
		int count = 0;
		for (int i = 0; str1[i] != '\0'; i++)
		{
			if (str1[i] == str2[i])
			{
				count++;
			}
		}
		if (count = strlen(str1) && count == strlen(str2))
			return true;
		else
			return false;
	}
	static bool stringSearch(char *str1, const char *str2)
	{
		int count = 0, move = 0;
		for (int i = 0; str1[i] != '\0'; i++)
		{
			for (int j = i; str1[j] == str2[move]; j++)
			{
				if (str1[j] != '\0')
				{
					count++; move++;
				}
			}
			if (count == Helper::strlen(str2))
			{
				return true;
			}
			else
			{
				count = 0; move = 0;
			}
		}
		return false;
	}
};

class Object
{
private:
	char* id;
public:
	virtual void PrintListView() = 0;
	virtual ~Object()
	{
		if (id != nullptr)
			delete[] id;
	}
	char* getID()
	{
		return id;
	}
	void setID(char* _id)
	{
		id = new char[Helper::strlen(_id) + 1];
		Helper::strCopy(id, _id);
	}
	void setIDNum(int num)
	{
		int move = 0;
		char buffer[10];
		for (int i = num; i >= 1; i /= 10)
			buffer[move++] = (i % 10) + '0';
		id = new char[Helper::strlen(buffer) + 1];
		Helper::strCopy(id, buffer);
	}
};

class Date
{
private:
	int Day;
	int Month;
	int Year;
public:
	static Date currentDate;
	Date()
	{
		Day = Month = Year = 0;
	}
	Date(int _Day, int _Month, int _Year)
	{
		Day = _Day;
		Month = _Month;
		Year = _Year;
	}
	void setDay(char* day)
	{
		Day = 0;
		int size = Helper::strlen(day);
		for (int i = 0; i < size; i++)
		{
			Day += day[i] - '0';
			if (i + 1 < size)
				Day *= 10;
		}
	}
	void setDayNum(int day)
	{
		Day = day;
	}
	int getDay()
	{
		return Day;
	}
	void setMonth(char* month)
	{
		Month = 0;
		int size = Helper::strlen(month);
		for (int i = 0; i < size; i++)
		{
			Month += month[i] - '0';
			if (i + 1 < size)
				Month *= 10;
		}
	}
	void setMonthNum(int month)
	{
		Month = month;
	}
	int getMonth()
	{
		return Month;
	}
	void setYear(char* year)
	{
		Year = 0;
		int size = Helper::strlen(year);
		for (int i = 0; i < size; i++)
		{
			Year += year[i] - '0';
			if (i + 1 < size)
				Year *= 10;
		}
	}
	void setYearNum(int year)
	{
		Year = year;
	}
	int getYear()
	{
		return Year;
	}
};

class User : public Object
{
private:
	char* fName;
	char* lName;
	User ** friendList;
	Page ** likedPages;
	Post ** timeline;
public:
	User()
	{
		fName = nullptr;
		lName = nullptr;
		friendList = nullptr;
		likedPages = nullptr;
		timeline = nullptr;
	}
	~User();
	User& getUser(ifstream &fin);
	User** getFriends()
	{
		return friendList;
	}
	User* getFriendIndex(int index)
	{
		return friendList[index];
	}
	void setFriendIndex(int index, User *ptr)
	{
		delete friendList[index];
		friendList[index] = ptr;
	}
	Page** getLikedPages()
	{
		return likedPages;
	}
	Page* getLikedPageIndex(int index)
	{
		return likedPages[index];
	}
	void setLikedPageIndex(int index, Page *ptr);
	void setTimeline(Post *ptr)
	{
		int i;
		if (timeline == nullptr)
		{
			timeline = new Post*[10];
			for (int i = 0; i < 10; i++)
				timeline[i] = nullptr;
		}
		for (i = 0; timeline[i] != nullptr; i++)
		{
		}
		timeline[i] = ptr;
	}
	char* getfName()
	{
		return fName;
	}
	char* getlName()
	{
		return lName;
	}
	Post** getTimeline()
	{
		return timeline;
	}
	Post* getTimelineIndex(int index)
	{
		if (timeline[index] != nullptr)
			return timeline[index];
		else
			return nullptr;
	}
	void PrintListView()
	{
		cout << fName << " " << lName;
	}
	void viewFriendList()
	{
		cout << "Command:\tView Friend List" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << fName << " " << lName << "--" << "Friend List\n" << endl;
		if (friendList != nullptr)
		{
			for (int i = 0; i < 10; i++)
			{
				if (friendList[i] != nullptr)
				{
					cout << friendList[i]->getID() << " - " << friendList[i]->getfName() << " " << friendList[i]->getlName() << endl;
				}
				else
					break;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	void viewLikedPages();
	void viewHome();
	void viewTimeline();
	void likePost(const char* postID);
	void PostComment(const char* postID, const char* commentDescp);
	void SharePost(const char* postID);
	void newPost(Post *ptr);
};

class Page : public Object
{
private:
	char* name;
	User ** followers;
	Post ** timeline;
public:
	Page()
	{
		name = nullptr;
		followers = nullptr;
		timeline = nullptr;
	}
	~Page();
	Page& getPage(ifstream &fin)
	{
		char buffer[100], ch;

		fin >> buffer; //Read ID
		setID(buffer);
		fin.get(ch);

		fin.getline(buffer, 100); //Read Name
		name = new char[Helper::strlen(buffer) + 1];
		Helper::strCopy(name, buffer);

		return *this;

	}
	void setTimeline(Post *ptr)
	{
		int i;
		if (timeline == nullptr)
		{
			timeline = new Post*[10];
			for (int i = 0; i < 10; i++)
				timeline[i] = nullptr;
		}
		for (i = 0; timeline[i] != nullptr; i++)
		{}
		timeline[i] = ptr;
	}
	void setFollower(User *ptr)
	{
		int i;
		if (followers == nullptr)
		{
			followers = new User*[10];
			for (int i = 0; i < 10; i++)
				followers[i] = nullptr;
		}
		for (i = 0; followers[i] != nullptr; i++)
		{}
		followers[i] = ptr;
	}
	char* getName()
	{
		return name;
	}
	void PrintListView()
	{
		cout << name;
	}
	Post** getTimeline()
	{
		return timeline;
	}
	Post* getTimelineIndex(int index)
	{
		if (timeline[index] != nullptr)
			return timeline[index];
		else
			return nullptr;
	}
	void viewTimeline();
};

class Post : public Object
{
private:
	Date date;
	char* descp;
	Object ** Liked;
	Object ** Shared;
	int totalLikes;
	Comment ** comments;
public:
	Post()
	{
		descp = nullptr;
		Liked = nullptr;
		Shared = nullptr;
		comments = nullptr;
		totalLikes = 0;
	}
	~Post();
	Post(char* _descp, Object *ptr);
	Post& getPost(ifstream &fin)
	{
		char buffer[100], ch;

		fin >> buffer; //Read ID
		setID(buffer);

		fin >> buffer; //Read Date
		date.setDay(buffer);
		fin >> buffer;
		date.setMonth(buffer);
		fin >> buffer;
		date.setYear(buffer);

		fin.get(ch);
		fin.getline(buffer, 100); //Read Descp
		descp = new char[Helper::strlen(buffer) + 1];
		Helper::strCopy(descp, buffer);

		fin >> buffer; //Read Shared Users/Pages
		if (!Helper::checkString(buffer, "-1"))
		{
			Shared = new Object*[1];
			if (buffer[0] == 'u')
				Shared[0] = new User;
			else
				Shared[0] = new Page;
			Shared[0]->setID(buffer);
		}
		fin >> buffer;  //Read Liked Users/Pages
		if (!Helper::checkString(buffer, "-1"))
		{
			int i;
			Liked = new Object*[10];
			for (i = 0; !Helper::checkString(buffer, "-1"); i++)
			{
				if (buffer[0] == 'u')
					Liked[i] = new User;
				else
					Liked[i] = new Page;

				totalLikes++;
				Liked[i]->setID(buffer);
				fin >> buffer;
			}
			for (; i < 10; i++)
				Liked[i] = nullptr;
		}
		fin >> buffer;
		fin.getline(buffer, 100);
			
		return *this;
	}
	void linkComment(Comment &obj)
	{
		int j;
		if (comments == nullptr)
		{
			comments = new Comment*[10];
			for (int i = 0; i < 10; i++)
				comments[i] = nullptr;
		}
		for (j = 0; comments[j] != nullptr; j++)
		{}
		comments[j] = &obj;
	}
	char* getDescp()
	{
		return descp;
	}
	Object** getShared()
	{
		return Shared;
	}
	Object* getSharedIndex(int index)
	{
		return Shared[index];
	}
	void setShared(Object *ptr)
	{
		delete Shared[0];
		Shared[0] = ptr;
	}
	Object** getLiked()
	{
		return Liked;
	}
	Object* getLikedIndex(int index)
	{
		return Liked[index];
	}
	void setLikedIndex(int index, Object *ptr)
	{
		delete Liked[index];
		Liked[index] = ptr;
	}
	bool CompareDate()
	{
		if (date.getDay() == Date::currentDate.getDay() || date.getDay() == (Date::currentDate.getDay() - 1))
		{
			if (date.getMonth() == Date::currentDate.getMonth())
			{
				if (date.getYear() == Date::currentDate.getYear())
				{
					return true;
				}
			}
		}
		return false;
	}
	void PrintPost();
	void PrintListView()
	{
		if (Liked != nullptr)
		{
			for (int i = 0; i < 10; i++)
			{
				if (Liked[i] != nullptr)
				{
					cout << Liked[i]->getID() << "--";
					Liked[i]->PrintListView();
					cout << endl;
				}
				else
					break;
			}
		}
	}
	void AddLike(Object *ptr)
	{
		int i;
		if (Liked != nullptr)
		{
			for (i = 0; Liked[i] != nullptr; i++)
			{}
			Liked[i] = ptr;
		}
		else
		{
			Liked = new Object*[10];
			for (int i = 0; i < 10; i++)
				Liked[i] = nullptr;
			Liked[0] = ptr;
		}
	}
	void AddComment(const char* _descp, Object *ptr);
};

class Comment : public Object
{
private:
	Object * commentedBy;
	char* descp;
public:
	Comment()
	{
		commentedBy = nullptr;
		descp = nullptr;
	}
	~Comment();
	void setCommentedBy(Object &obj)
	{
		commentedBy = &obj;
	}
	void setDescp(char* _descp)
	{
		descp = new char[Helper::strlen(_descp) + 1];
		Helper::strCopy(descp, _descp);
	}
	Object* getCommentedBy()
	{
		return commentedBy;
	}
	char* getDescp()
	{
		return descp;
	}
	void setComment(const char* _descp, Object *ptr);
	void PrintListView()
	{
		//Do Nothing
	}
};

class Social
{
private:
	User ** users;
	Page ** pages;
	Post ** posts;
	Comment ** comments;
	User * currentUser;
public:
	static int userCount;
	static int pageCount;
	static int postCount;
	static int commentCount;

	Social()
	{
		users = nullptr;
		pages = nullptr;
		posts = nullptr;
		comments = nullptr;
		currentUser = nullptr;
	}
	~Social()
	{
		for (int i = 0; i < userCount; i++)
			delete users[i];
		delete[] users;

		for (int i = 0; i < pageCount; i++)
			delete pages[i];
		delete[] pages;

 		delete[] posts;

		delete[] comments;
	}
	void readAndLinkComments(ifstream &fin, int index)
	{
		char buffer[100], ch;
		bool flag = false;
		comments[index] = new Comment;

		fin >> buffer; //Read ID
		comments[index]->setID(buffer);

		fin >> buffer; //Link post to comment[index]
		for (int i = 0; i < postCount; i++)
		{
			if (Helper::checkString(buffer, posts[i]->getID()))
			{
				posts[i]->linkComment(*comments[index]);
				break;
			}
		}

		fin >> buffer; //Link commentedBy to User
		for (int i = 0; i < userCount; i++)
		{
			if (Helper::checkString(buffer, users[i]->getID()))
			{
				comments[index]->setCommentedBy(*users[i]);
				flag = true;
				break;
			}
		}
		for (int i = 0; i < pageCount && flag == false; i++) //Link commentedBy to Page
		{
			if (Helper::checkString(buffer, pages[i]->getID()))
			{
				comments[index]->setCommentedBy(*pages[i]);
				break;
			}
		}

		fin.get(ch); //Read Descp
		fin.getline(buffer, 100);
		comments[index]->setDescp(buffer);

	}
	void LoadData(ifstream &fin)
	{
		char buffer[200], ch = '\0';

		fin.open("16.2.2 - Project-SocialNetworkUsers.txt");
		fin >> userCount;
		for (int i = 0; i < 3; i++) //Read Junk
			fin.getline(buffer, 200);
		
		users = new User*[userCount];
		for (int i = 0; i < userCount; i++) //Read Users
		{
			users[i] = new User;
			users[i]->getUser(fin);
		}
		fin.close();

		fin.open("16.2.3. - Project-SocialNetworkPages.txt");
		fin >> pageCount;
		for (int i = 0; i < 3; i++) //Read Junk
			fin.getline(buffer, 200);
		pages = new Page*[pageCount];
		for (int i = 0; i < pageCount; i++) //Read Pages
		{
			pages[i] = new Page;
			pages[i]->getPage(fin);
		}
		fin.close();

		fin.open("16.2.4 - Project-SocialNetworkPosts.txt");
		fin >> postCount;
		for (int i = 0; i < 8; i++) //Read Junk
			fin.getline(buffer, 200);
		posts = new Post*[postCount];
		for (int i = 0; i < postCount; i++) //Read Posts
		{
			posts[i] = new Post;
			posts[i]->getPost(fin);
		}
		fin.close();

		fin.open("16.2.5 - Project-SocialNetworkComments.txt");
		fin >> commentCount;
		for (int i = 0; i < 3; i++) //Read Junk
			fin.getline(buffer, 200);
		comments = new Comment*[commentCount];
		for (int i = 0; i < commentCount; i++)
		{
			readAndLinkComments(fin, i);
		}
		fin.close();
	}
	int search(Object* Search)
	{
		for (int i = 0; i < userCount; i++) //Search Users 
		{
			if (Helper::checkString(users[i]->getID(), Search->getID()))
			{
				return i;
			}
		}

		for (int i = 0; i < pageCount; i++) //Search Pages
		{
			if (Helper::checkString(pages[i]->getID(), Search->getID()))
			{
				return i;
			}
		}

		return 0;
	}
	void LinkData()
	{
		for (int i = 0; i < userCount; i++) //Link Users->FriendLists to users
		{
			if (users[i]->getFriends() != nullptr)
			{
				for (int j = 0; j < userCount; j++)
				{
					if (users[i]->getFriendIndex(j) != nullptr) //Check if friendList[j] != nullptr for the end of the list
					{
						int index = search(users[i]->getFriendIndex(j));
						users[i]->setFriendIndex(j, users[index]);
					}
					else
						break;
				}
			}
		}

		for (int i = 0; i < userCount; i++) //Link Users->LikedPages to Pages ||||||| Also link Page to their followers
		{
			if (users[i]->getLikedPages() != nullptr)
			{
				for (int j = 0; j < userCount; j++)
				{
					if (users[i]->getLikedPageIndex(j) != nullptr) //Check if likedPage[j] != nullptr for the end of the list
					{
						int index = search(users[i]->getLikedPageIndex(j));
						users[i]->setLikedPageIndex(j, pages[index]);
						pages[index]->setFollower(users[i]);
					}
					else
						break;
				}
			}
		}

		for (int i = 0; i < postCount; i++) //Linking posts->Shared to Users/Pages ||||||| Also Linking timeline of User/Page with posts
		{
			if (posts[i]->getShared() != nullptr)
			{
				int index = search(posts[i]->getSharedIndex(0));

				if (posts[i]->getSharedIndex(0)->getID()[0] == 'u') //Check if user shared
				{
					posts[i]->setShared(users[index]);
					users[index]->setTimeline(posts[i]);
				}	
				else if (posts[i]->getSharedIndex(0)->getID()[0] == 'p') //Check if page shared
				{
					posts[i]->setShared(pages[index]);
					pages[index]->setTimeline(posts[i]);
				}
			}
		}

		for (int i = 0; i < postCount; i++) //Linking posts->Liked to Users/Pages
		{
			if (posts[i]->getLiked() != nullptr)
			{
				for (int j = 0; j < postCount; j++)
				{
					if (posts[i]->getLikedIndex(j) != nullptr)
					{
						int index = search(posts[i]->getLikedIndex(j));

						if (posts[i]->getLikedIndex(j)->getID()[0] == 'u') //Check if user liked
							posts[i]->setLikedIndex(j, users[index]);
						else if (posts[i]->getLikedIndex(j)->getID()[0] == 'p') //Check if page liked
							posts[i]->setLikedIndex(j, pages[index]);
					}
					else
						break;
				}
			}
		}
	}
	void SetCurrentUser(const char* userID)
	{
		cout << "Command:	Set current user " << userID << endl;
		for (int i = 0; i < userCount; i++)
		{
			if (Helper::checkString(users[i]->getID(), userID))
			{
				cout << users[i]->getfName() << " " << users[i]->getlName() << " successfully set as Current User." << endl << endl;
				currentUser = users[i];
				break;
			}
		}
	}
	void SetCurrentDate(int day, int month, int year)
	{
		cout << "Command:	Set current System Date " << day << " " << month << " " << year << endl;
		Date::currentDate.setDayNum(day);
		Date::currentDate.setMonthNum(month);
		Date::currentDate.setYearNum(year);
		cout << "System Date:\t";
		cout << Date::currentDate.getDay() << "/" << Date::currentDate.getMonth() << "/" << Date::currentDate.getYear() << endl << endl;
	}
	void viewLikedList(const char* postID)
	{
		cout << "Command:\tViewLikedList(" << postID << ")" << endl << endl;
		cout << "Post Liked By:" << endl; 
		for (int i = 0; i < postCount; i++)
		{
			if (Helper::checkString(posts[i]->getID(), postID))
			{
				posts[i]->PrintListView();
				break;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	void viewPost(const char* postID)
	{
		cout << "Command:\tViewPost(" << postID << ")" << endl << endl;
		for (int i = 0; i < postCount; i++)
		{
			if (Helper::checkString(posts[i]->getID(), postID))
			{
				posts[i]->PrintPost();
				break;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	void viewPage(const char* pageID)
	{
		cout << "Command:\tViewPage(" << pageID << ")" << endl << endl;
		for (int i = 0; i < postCount; i++)
		{
			if (Helper::checkString(pages[i]->getID(), pageID))
			{
				pages[i]->viewTimeline();
				break;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	void Search(const char* toFind)
	{
		cout << "\nCommand:	Search(" << toFind << ")" << endl << endl;
		cout << "Users: " << endl;
		for (int i = 0; i < userCount; i++)
		{
			if (Helper::stringSearch(users[i]->getfName(), toFind) || Helper::stringSearch(users[i]->getlName(), toFind))
			{
				cout << "--";
				cout << users[i]->getID() << " - ";
				users[i]->PrintListView();
				cout << endl;
			}
		}
		cout << "Posts: " << endl;
		for (int i = 0; i < postCount - 2; i++)
		{
			if (Helper::stringSearch(posts[i]->getDescp(), toFind))
			{
				cout << "--";
				cout << posts[i]->getID() << " - ";
				posts[i]->getShared()[0]->PrintListView();
				cout << " shared ";
				posts[i]->PrintPost();
			}
		}
		cout << "Pages: " << endl;
		for (int i = 0; i < pageCount; i++)
		{
			if (Helper::stringSearch(pages[i]->getName(), toFind))
			{
				cout << "--";
				cout << pages[i]->getID() << " - ";
				pages[i]->PrintListView();
				cout << endl;
			}
		}
	}
	void Run()
	{
		SetCurrentUser("u7");
		SetCurrentDate(15, 11, 2017);
		currentUser->viewFriendList();
		currentUser->viewLikedPages();
		currentUser->viewHome();
		currentUser->viewTimeline();
		viewLikedList("post5");
		currentUser->likePost("post5");
		viewLikedList("post5");

		currentUser->PostComment("post4", "Good Luck for your Result");
		viewPost("post4");
		currentUser->PostComment("post8", "Thanks for the wishes");
		viewPost("post8");
		currentUser->SharePost("post5");
		currentUser->viewTimeline();

		viewPage("p1");
		Search("Ali");
	}
};

int Social::userCount = 0;
int Social::pageCount = 0;
int Social::postCount = 0;
int Social::commentCount = 0;
Date Date::currentDate(0, 0, 0);

//User Methods
User& User::getUser(ifstream &fin)
{
	char buffer[100];
	bool flag = false;

	fin >> buffer; //Read ID
	setID(buffer);

	fin >> buffer; //Read fName
	fName = new char[Helper::strlen(buffer) + 1];
	Helper::strCopy(fName, buffer);

	fin >> buffer; //Read lName
	lName = new char[Helper::strlen(buffer) + 1];
	Helper::strCopy(lName, buffer);

	fin >> buffer; //Read Freind List
	friendList = new User*[10];
	for (int i = 0; i < 10; i++)
	{
		if (!Helper::checkString(buffer, "-1") && flag == false)
		{
			friendList[i] = new User;
			friendList[i]->setID(buffer);
			fin >> buffer;
		}
		else if (Helper::checkString(buffer, "-1") && flag == false)
		{
			friendList[i] = nullptr;
			flag = true;
		}
		else if (flag == true)
			friendList[i] = nullptr;
	}

	fin >> buffer; //Read Liked Pages
	flag = false;
	likedPages = new Page*[10];
	for (int i = 0; i < 10; i++)
	{
		if (!Helper::checkString(buffer, "-1") && flag == false)
		{
			likedPages[i] = new Page;
			likedPages[i]->setID(buffer);
			fin >> buffer;
		}
		else if (Helper::checkString(buffer, "-1") && flag == false)
		{
			likedPages[i] = nullptr;
			flag = true;
		}
		else if (flag == true)
			likedPages[i] = nullptr;
	}
	return *this;
}
void User::viewLikedPages()
{
	cout << "Command:\tView Liked Pages" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << fName << " " << lName << "--" << "Liked Pages\n" << endl;
	if (likedPages != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (likedPages[i] != nullptr)
			{
				cout << likedPages[i]->getID() << " - " << likedPages[i]->getName() << endl;
			}
			else
				break;
		}
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
}
void User::viewHome()
{
	cout << "Command:\tView Home" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << fName << " " << lName << "--" << "Home Page\n" << endl;

	if (friendList != nullptr) //Friends posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (friendList[i] != nullptr) //Friend null check
			{
				if (friendList[i]->getTimeline() != nullptr) //Friend->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (friendList[i]->getTimelineIndex(j) != nullptr) //Friend->timeline[j] null check
						{
							if (friendList[i]->getTimelineIndex(j)->CompareDate()) //Comapare with currentDate
							{
								cout << "---" << friendList[i]->getfName() << " " << friendList[i]->getlName() << " shared:  ";
								friendList[i]->getTimelineIndex(j)->PrintPost();
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	if (likedPages != nullptr) //LikedPages Posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (likedPages[i] != nullptr) //LikedPage null check
			{
				if (likedPages[i]->getTimeline() != nullptr) //LikedPage->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (likedPages[i]->getTimelineIndex(j) != nullptr) //LikedPage->timeline[j] null check
						{
							if (likedPages[i]->getTimelineIndex(j)->CompareDate()) //Comapare with currentDate
							{
								cout << "---" << likedPages[i]->getName() << " shared:  ";
								likedPages[i]->getTimelineIndex(j)->PrintPost();
							}
						}
						else
							break;
					}
				}
			}
		}
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
}
void User::likePost(const char* postID)
{
	bool flag = false;
	cout << "Command:\tLikePost(" << postID << ")" << endl;
	if (friendList != nullptr) //Friends posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (friendList[i] != nullptr) //Friend null check
			{
				if (friendList[i]->getTimeline() != nullptr) //Friend->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (friendList[i]->getTimelineIndex(j) != nullptr) //Friend->timeline[j] null check
						{
							if (Helper::checkString(friendList[i]->getTimelineIndex(j)->getID(), postID))
							{
								friendList[i]->getTimelineIndex(j)->AddLike(this);
								flag = true;
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	if (likedPages != nullptr && flag == false) //LikedPages Posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (likedPages[i] != nullptr) //LikedPage null check
			{
				if (likedPages[i]->getTimeline() != nullptr) //LikedPage->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (likedPages[i]->getTimelineIndex(j) != nullptr) //LikedPage->timeline[j] null check
						{
							if (Helper::checkString(likedPages[i]->getTimelineIndex(j)->getID(), postID))
							{
								likedPages[i]->getTimelineIndex(j)->AddLike(this);
								flag = true;
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	if (timeline != nullptr) //Check timeline
	{
		for (int i = 0; i < 10; i++)
		{
			if (timeline[i] != nullptr)
			{
				if (Helper::checkString(timeline[i]->getID(), postID))
				{
					timeline[i]->AddLike(this);
					flag = true;
				}
			}
			else
				break;
		}
	}

	if (flag == false)
		cout << "Post Not Found and cant be liked" << endl;

}
void User::viewTimeline()
{
	cout << "Command:\tView Timeline" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << fName << " " << lName << "--" << "Timeline\n" << endl;
	if (timeline != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (timeline[i] != nullptr)
			{
				timeline[i]->PrintPost();
			}
			else
				break;
		}
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
}
void User::PostComment(const char* postID, const char* commentDescp)
{
	bool flag = false;
	cout << "Command:\tPostComment(" << postID << ", " << commentDescp << ")" << endl;
	if (friendList != nullptr) //Friends posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (friendList[i] != nullptr) //Friend null check
			{
				if (friendList[i]->getTimeline() != nullptr) //Friend->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (friendList[i]->getTimelineIndex(j) != nullptr) //Friend->timeline[j] null check
						{
							if (Helper::checkString(friendList[i]->getTimelineIndex(j)->getID(), postID))
							{
								friendList[i]->getTimelineIndex(j)->AddComment(commentDescp, this);
								flag = true;
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	if (likedPages != nullptr && flag == false) //LikedPages Posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (likedPages[i] != nullptr) //LikedPage null check
			{
				if (likedPages[i]->getTimeline() != nullptr) //LikedPage->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (likedPages[i]->getTimelineIndex(j) != nullptr) //LikedPage->timeline[j] null check
						{
							if (Helper::checkString(likedPages[i]->getTimelineIndex(j)->getID(), postID))
							{
								likedPages[i]->getTimelineIndex(j)->AddComment(commentDescp, this);
								flag = true;
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	if (timeline != nullptr) //Check timeline
	{
		for (int i = 0; i < 10; i++)
		{
			if (timeline[i] != nullptr)
			{
				if (Helper::checkString(timeline[i]->getID(), postID))
				{
					timeline[i]->AddComment(commentDescp, this);
					flag = true;
				}
			}
			else
				break;
		}
	}

	if (flag == false)
		cout << "Post Not Found and cant be commented" << endl;
}
void User::SharePost(const char* postID)
{
	bool flag = false;
	cout << "Command:\tSharePost(" << postID << ")" << endl;
	if (friendList != nullptr) //Friends posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (friendList[i] != nullptr) //Friend null check
			{
				if (friendList[i]->getTimeline() != nullptr) //Friend->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (friendList[i]->getTimelineIndex(j) != nullptr) //Friend->timeline[j] null check
						{
							if (Helper::checkString(friendList[i]->getTimelineIndex(j)->getID(), postID))
							{
								newPost(friendList[i]->getTimelineIndex(j));
								flag = true;
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	if (likedPages != nullptr && flag == false) //LikedPages Posts
	{
		for (int i = 0; i < 10; i++)
		{
			if (likedPages[i] != nullptr) //LikedPage null check
			{
				if (likedPages[i]->getTimeline() != nullptr) //LikedPage->timeline null check
				{
					for (int j = 0; j < 10; j++)
					{
						if (likedPages[i]->getTimelineIndex(j) != nullptr) //LikedPage->timeline[j] null check
						{
							if (Helper::checkString(likedPages[i]->getTimelineIndex(j)->getID(), postID))
							{
								newPost(likedPages[i]->getTimelineIndex(j));
								flag = true;
							}
						}
						else
							break;
					}
				}
			}
		}
	}

	//No check for timeline as cant share same thing twice

	if (flag == false)
		cout << "Post Not Found and cant be commented" << endl;
}
void User::newPost(Post *ptr)
{
	int i;
	if (timeline == nullptr)
	{
		timeline = new Post*[10];
		for (int i = 0; i < 10; i++)
			timeline[i] = nullptr;
	}
	for (i = 0; timeline[i] != nullptr; i++)
	{
	}
	timeline[i] = new Post(ptr->getDescp(), this);
}
void User::setLikedPageIndex(int index, Page *ptr)
{
	delete likedPages[index];
	likedPages[index] = ptr;
}
User::~User()
{
	if (fName != nullptr)
		delete[] fName;
	if (lName != nullptr)
		delete[] lName;
	if (friendList != nullptr)
		delete[] friendList;
	if (likedPages != nullptr)
		delete[] likedPages;
	if (timeline != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (timeline[i] != nullptr)
			{
				delete timeline[i];
			}
		}
		delete[] timeline;
	}
}
//Page Method
void Page::viewTimeline()
{
	if (timeline != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (timeline[i] != nullptr)
			{
				timeline[i]->PrintPost();
			}
			else
				break;
		}
	}
}
Page::~Page()
{
	if (name != nullptr)
		delete[] name;
	if (followers != nullptr)
		delete[] followers;
	if (timeline != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (timeline[i] != nullptr)
			{
				delete timeline[i];
			}
		}
		delete[] timeline;
	}
}
//Post Methods
void Post::PrintPost()
{
	cout << "'" << descp << "'" << "\t(" << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << ")" << endl;
	if (comments != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (comments[i] != nullptr)
			{
				cout << "\t\t";
				comments[i]->getCommentedBy()->PrintListView();
				cout << " wrote:" << "'" << comments[i]->getDescp() << "'" << endl;
			}
			else
				break;
		}
	}
}
void Post::AddComment(const char* _descp, Object *ptr)
{
	int i;
	if (comments != nullptr)
	{
		for (i = 0; comments[i] != nullptr; i++)
		{
		}
		comments[i] = new Comment;
		comments[i]->setComment(_descp, ptr);
	}
	else
	{
		comments = new Comment*[10];
		for (int i = 0; i < 10; i++)
			comments[i] = nullptr;
		comments[0]->setComment(_descp, ptr);
	}
}
Post::Post(char* _descp, Object *ptr)
{
	int count = ++Social::postCount;
	setIDNum(count);

	date.setDayNum(Date::currentDate.getDay());
	date.setMonthNum(Date::currentDate.getMonth());
	date.setYearNum(Date::currentDate.getYear());

	descp = new char[Helper::strlen(_descp) + 1];
	Helper::strCopy(descp, _descp);

	Liked = nullptr;

	Shared = new Object*[1];
	Shared[0] = ptr;

	totalLikes = 0;

	comments = nullptr;
}
Post::~Post()
{
	if (descp != nullptr)
		delete[] descp;
	if (Liked != nullptr)
		delete[] Liked;
	if (Shared != nullptr)
		delete[] Shared;
	if (comments != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (comments[i] != nullptr)
			{
				delete comments[i];
			}
		}
		delete[] comments;
	}
}
//Comment Methods
void Comment::setComment(const char* _descp, Object *ptr)
{
	int count = ++Social::commentCount;
	setIDNum(count);

	commentedBy = ptr;

	descp = new char[Helper::strlen(_descp) + 1];
	Helper::strCopy(descp, _descp);
}
Comment::~Comment()
{
	if (descp != nullptr)
		delete[] descp;
}

int main()
{
	ifstream fin;
	Social network;
	network.LoadData(fin);
	network.LinkData(); 
	network.Run();
	system("pause");
}