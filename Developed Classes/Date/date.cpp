#include "date.h"

#define INTEIRO -100
#define DECIMAL -200
#define U_INTEIRO -300

Date::Date()
{
time_t theTime = time(NULL);

struct tm *aTime = localtime(&theTime);

this->day = aTime->tm_mday;

this->month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept

this->year = aTime->tm_year + 1900;
}

Date::Date(unsigned int year, unsigned int month,unsigned int day)
{
  this->year = year;

  this->month = month;

  this->day = day;
}

Date::Date(string yearMonthDay)
{
  vector<string> fields;

  fields = tokenizer(yearMonthDay,"/");

  if(fields.size() != 3)
  {
    cerr << "Insira uma data com duas '/'!\n";
    exit(1);
  }

  for(auto i = fields.begin(); i != fields.end(); i++)
  {
    if(!validAnswer(*i, U_INTEIRO))
    {
      cerr << "Insira numeros separados por '/' (yyyy/mm/dd)!\n";
      exit(1);
    }
  }

  this->year = (unsigned int)stoi(fields[0]);

  this->month = (unsigned int)stoi(fields[1]);

  this->day = (unsigned int)stoi(fields[2]);
}

int Date::compare(const Date& right) const
{
  return (right.getYear() - this->year)*365 + (right.getMonth() - this->month)*31\
   + (right.getDay() - this->day);
}

void Date::setYear(unsigned int year)
{
  this->year = year;
}

void Date::setMonth(unsigned int month)
{
  this->month = month;
}

void Date::setDay(unsigned int day)
{
  this->day = day;
}

void Date::setDate(unsigned int year, unsigned int month, unsigned int day)
{
  setYear(year);

  setMonth(month);

  setDay(day);
}

unsigned int Date::getYear() const
{
  return year;
}

unsigned int Date::getMonth() const
{
  return month;
}

unsigned int Date::getDay() const
{
  return day;
}

string Date::getDate() const
{
  ostringstream outstr;

  outstr << right << setfill('0') << setw(4) << year << "/" << setw(2) << month << "/" << setw(2) << day;

  return outstr.str();
}

void Date::show()
{
  cout << right << setfill('0') << setw(4) << year << "/" << setw(2) << month << "/" << setw(2) << day << endl;
}

bool Date::biSsexto()
{
  if(year % 4 == 0 && year % 100 != 0 && year % 400 != 0)
    return true;
  else
    return false;
}

unsigned int Date::maxMonthDays()
{
    switch (month)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        return 31;
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
      case 2:
        if(biSsexto())
          return 29;
        else
          return 28;
      default:
        return 0;
    }
}

bool Date::isValid()
{
  if(day > maxMonthDays())
    return false;
  else
    return true;
}

bool operator == (const Date& left, const Date& right)
{
  if(left.compare(right) == 0)
    return true;
  else
    return false;
}

bool operator != (const Date& left, const Date& right)
{
  if(left.compare(right) != 0)
    return true;
  else
    return false;
}

bool operator>(const Date& left, const Date& right)
{
  if(left.compare(right) > 0)
    return true;
  else
    return false;
}

bool operator<(const Date& left, const Date& right)
{
  if(left.compare(right) < 0)
    return true;
  else
    return false;
}

string get_token(string to_token, size_t begin, size_t end)
{
  string tokenized;

  for(size_t i = begin; i < end; i++)
    tokenized.push_back(to_token.at(i));

  return tokenized;
}

vector<string> tokenizer (string to_token, string token)
{
  size_t found, last_found = -1;

	vector<string> tokens;

	while ((found = to_token.find(token, last_found + 1)) != to_token.npos)
	{
		tokens.push_back(get_token(to_token, last_found + 1, found));
		last_found = found;
	}

	tokens.push_back(get_token(to_token, last_found + 1, to_token.size()));

  return tokens;
}

vector<int> int_tokenizer (string to_token, string token)
{
  vector<string> to_convert;
  vector<int> to_return;

  to_convert = tokenizer(to_token, token);

  for(int i = 0; i < (int)to_convert.size(); i++)
    to_return.push_back(stoi(to_convert[i]));

  return to_return;
}

bool validAnswer(string answer, int type)
{
  switch(type)
  {
    case INTEIRO:
      try
      {
        stoi(answer);
      }
      catch (const std::invalid_argument& ia)
      {
        return false;
      }
      catch(std::out_of_range& ia)
      {
        return false;
      }
      break;
    case DECIMAL:
      try
      {
        stof(answer);
      }
      catch (const std::invalid_argument& ia)
      {
        return false;
      }
      catch (const std::out_of_range& ia)
      {
        return false;
      }
      break;
    case U_INTEIRO:
      try
      {
        stoi(answer);
      }
      catch (const std::invalid_argument& ia)
      {
        return false;
      }
      catch(std::out_of_range& ia)
      {
        return false;
      }
      if(stoi(answer) < 0)
        return false;
      break;
  }

  return true;
}
