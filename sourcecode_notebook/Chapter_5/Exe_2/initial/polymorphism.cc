#include <iostream>
#include <memory>
#include <string>

class Doctor
{
   protected:
      unsigned doctor_id;
      std::shared_ptr<Doctor> assistant;

   public:

      Doctor(unsigned id) : doctor_id(id){}

      virtual void print_id (void) const
      {
         std::cout << "Doctor id: " << doctor_id << "\n";
      }

      void assign_assistant(const std::shared_ptr<Doctor> &ptr)
      {
         this -> assistant = ptr;
      }

      virtual ~Doctor (void) {}
};

class Surgeon : public Doctor
{
   public:

      std::string specialty;

      Surgeon(unsigned id, std::string s) : Doctor(id), specialty(s){}

      virtual void print_id (void) const override
      {
         std::cout << "Surgeon id: " << doctor_id << "\n";
      }

      virtual void print_specialty (void) const
      {
         std::cout << "Specialty: " << specialty << "\n";
      }

      virtual void operate(void) const
      {
         std::cout << "Surgery Responsible: " << std::endl;
         this -> print_id ();
         std::cout << "Surgery Assistant: " << std::endl;
         this -> assistant -> print_id ();
      }

      virtual ~Surgeon (void) {}
};

int main (void)
{
   Doctor dt1 (1);
   Doctor dt2 (2);
   Surgeon dt3 (3, "General");
   Surgeon dt4 (4, "Neurological");

   dt2 = dt3;
   dt3 = dt1;

   Doctor &refY = dt3;
   Doctor * ptrX = &dt4;

   refY.print_id();
   ptrX->print_id();
   ptrX->print_specialty();

   std::shared_ptr<Doctor> ptrA = std::make_shared<Doctor> (dt1);
   std::shared_ptr<Doctor> ptrB = std::make_shared<Doctor> (dt2);
   std::shared_ptr<Doctor> ptrC = std::make_shared<Surgeon> (dt3);
   std::shared_ptr<Surgeon> ptrD = std::make_shared<Surgeon> (dt4);

   ptrB -> print_id ();
   ptrC -> assign_assistant (ptrB);
   ptrD -> assign_assistant (ptrA);

   ptrC -> operate ();
   ptrD -> operate ();
   return 0;
}
