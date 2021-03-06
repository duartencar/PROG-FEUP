#include "timeit.h"

#define INTEIRO -100
#define DECIMAL -200
#define U_INTEIRO -300

Timeit::Timeit()
{
  hours = 0;
  minutes = 0;
  seconds = 0;
  miliseconds = 0;
  HorM = true;
}

Timeit::Timeit(float rawTime)
{
  if(rawTime >= 3600)
  {
    hours = (unsigned int)((float)rawTime / 3600);

    rawTime -= hours * 3600;
  }
  else
    hours = 0;

  if(rawTime >= 60)
  {
    minutes = (unsigned int)((float)rawTime / 60);

    rawTime -= minutes * 60;
  }
  else
    minutes = 0;

  if(rawTime >= 1)
  {
    seconds = (unsigned int)rawTime;

    rawTime -= seconds;
  }
  else
    seconds = 0;

  miliseconds = rawTime * 1000;

  HorM = true;

  if(!valid())
  {
    cerr << "ERROR: OVERFLOW\n";

    exit(1);
  }
}

Timeit::Timeit(unsigned int hours, unsigned int min, unsigned int secs, unsigned int milis)
{
  this->hours = hours;

  this->minutes = min;

  this->seconds = secs;

  this->miliseconds = milis;

  this->HorM = true;

  if(!valid())
  {
    cerr << "ERROR: OVERFLOW\n";

    exit(1);
  }
}

Timeit::Timeit(string rawTime)
{
  vector<string> HmS = tokenizer(rawTime,":");

  if(HmS.size() !=  3)
  {
    cerr << "ERROR: String inserted hasn t got 2 ':'" << endl;
    exit(1);
  }
  vector<string> Sms = tokenizer(HmS[2],".");

  if(Sms.size() != 2)
  {
    cerr << "ERROR: hasn t got '.'" << endl;

    exit(1);
  }

  if(validAnswer(HmS[0], U_INTEIRO))
    hours = stoi(HmS[0]);
  else
  {
    cerr << "ERROR: Hour value read: " << HmS[0] << endl;
    exit(1);
  }

  if(validAnswer(HmS[1], U_INTEIRO))
    minutes = stoi(HmS[1]);
  else
  {
    cerr << "ERROR: Minute value read: " << HmS[1] << endl;
    exit(1);
  }

  if(validAnswer(Sms[0], U_INTEIRO))
    seconds = stoi(Sms[0]);
  else
  {
    cerr << "ERROR: Seconds value read: " << HmS[0] << endl;
    exit(1);
  }

  if(validAnswer(Sms[1], U_INTEIRO))
    miliseconds = stoi(Sms[1]);
  else
  {
    cerr << "ERROR: miliseconds value read: " << HmS[1] << endl;
    exit(1);
  }

  HorM = true;

  if(!valid())
  {
    cerr << "ERROR: OVERFLOW\n";

    exit(1);
  }
}

bool Timeit::getHorM() const
{
  return HorM;
}

void Timeit::setHorM_toFalse()
{
  HorM = false;
}

void Timeit::setHorM_toTrue()
{
  HorM = true;
}

bool Timeit::valid() const
{
  if(hours < 0 || hours > 99)
    return false;

  if(minutes < 0 || minutes > 60)
    return false;

  if(seconds < 0 || seconds > 60)
    return false;

  if(miliseconds < 0 || miliseconds > 1000)
    return false;

  return true;
}

int Timeit::compare(const Timeit& right) const
{
  return ((int)this->hours - (int)right.getHours())*3600000
      +  ((int)this->minutes - (int)right.getMinutes())*60000
      +  ((int)this->seconds - (int)right.getSeconds())*1000
      +  ((int)this->miliseconds - (int)right.getMiliSeconds());
}

unsigned int Timeit::getHours() const
{
  return hours;
}

unsigned int Timeit::getMinutes() const
{
  return minutes;
}

unsigned int Timeit::getSeconds() const
{
  return seconds;
}

unsigned int Timeit::getMiliSeconds() const
{
  return miliseconds;
}

void Timeit::setHours(unsigned int hours)
{
  this->hours = hours;
}

void Timeit::setMinutes(unsigned int minutes)
{
  this->minutes = minutes;
}

void Timeit::setSeconds(unsigned int seconds)
{
  this->seconds = seconds;
}

void Timeit::setMiliSeconds(unsigned int miliseconds)
{
  this->miliseconds = miliseconds;
}

void Timeit::Reset()
{
  this->hours = 0;

  this->minutes = 0;

  this->seconds = 0;

  this->miliseconds = 0;
}

void Timeit::Copy(const Timeit& to_copy)
{
  this->hours = to_copy.getHours();

  this->minutes = to_copy.getMinutes();

  this->seconds = to_copy.getSeconds();

  this->miliseconds = to_copy.getMiliSeconds();

  this->HorM = to_copy.getHorM();
}

string Timeit::getTime()
{
  ostringstream outstr;

  if(getHorM())
    outstr << right  << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes \
          << ":" << setw(2) << seconds << "." << left << setw(3) << miliseconds;
  else
    outstr << right << setfill('0') << setw(2) << minutes << ":" << setw(2) << seconds \
          << "." << left << setw(3) << miliseconds;

  return outstr.str();
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

bool operator == (const Timeit& left, const Timeit& right)
{
  if(left.compare(right) == 0)
    return true;
  else
    return false;
}

bool operator > (const Timeit& left, const Timeit& right)
{
  if(left.compare(right) > 0)
    return true;
  else
    return false;
}

bool operator < (const Timeit& left, const Timeit& right)
{
  if(left.compare(right) < 0)
    return true;
  else
    return false;
}

void operator << (const Timeit& left, const Timeit& right)
{
  left.Copy(right);
}

void operator >> (const Timeit& left, const Timeit& right)
{
  right.Copy(left);
}
