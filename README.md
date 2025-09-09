Small Clinic Management System
📌 Overview

This project is a Small Clinic Management System implemented in C++ using Object-Oriented Programming (OOP) principles.
It demonstrates the application of encapsulation, inheritance, polymorphism, constructors/destructors, and object management in a real-world scenario.

The system models a small family clinic that manages:

Patients (regular & chronic)

Doctors

Appointments

Clinic Manager (overall controller)

🎯 Features

Register patients (normal & chronic patients).

Manage doctors and their specialties.

Schedule, cancel, and complete appointments.

Maintain patient medical history.

Support inheritance (ChronicPatient inherits from Patient).

Demonstrate virtual methods override.

Destructor messages to confirm object lifecycle.

🧩 Class Design
1. Patient

Attributes: name, id, age, medicalHistory.

Methods: scheduleAppointment(), updateHistory(), displayInfo().

Virtual destructor and method override ready.

2. ChronicPatient (inherits from Patient)

Extra attributes: conditionType, lastCheckupDate.

Overrides scheduleAppointment() → prints different behavior for chronic cases.

3. Doctor

Attributes: name, id, specialty, assignedAppointments.

Methods: assignAppointment(), updateAppointmentStatus(), displayInfo().

4. Appointment

Attributes: date, time, reason, status, patient, doctor.

Methods: cancel(), complete(), display().

5. ClinicManager

Holds vectors of patients, doctors, appointments.

Responsible for memory cleanup via destructor.

Methods: addPatient(), addDoctor(), addAppointment(), showAllPatients(), showAllDoctors(), showAllAppointments().

🧪 Sample Output

When running main(), the program demonstrates:

Patient Alice created
Patient Bob created
ChronicPatient Charlie with condition Diabetes created
Doctor Dr. Smith created
Doctor Dr. John created
Doctor Dr. Alice created
Appointment created for Alice with Dr. Dr. Smith
Appointment created for Bob with Dr. Dr. John
Appointment created for Charlie with Dr. Dr. Alice
Patient Alice scheduled appointment on 2025-09-10 for General Checkup
Patient Bob scheduled appointment on 2025-09-12 for Dermatology Consult
ChronicPatient Charlie requires frequent check-ups. Appointment on 2025-09-15 for Diabetes Follow-up scheduled.
Appointment completed on 2025-09-10 10:00
Appointment canceled on 2025-09-12 14:00

--- All Patients ---
Patient(ID:1, Name:Alice, Age:30)
  Medical History:
   - 2025-07-01: Flu - Paracetamol
Patient(ID:2, Name:Bob, Age:40)
  Medical History:
   - 2025-08-05: Skin allergy - Antihistamine
ChronicPatient(ID:3, Name:Charlie, Condition:Diabetes, LastCheckup:2025-06-01)
  Medical History:
   - 2025-06-15: Diabetes check - Insulin

--- All Doctors ---
Doctor(ID:101, Name:Dr. Smith, Specialty:Cardiology)
  Assigned Appointments:
   - 2025-09-10 10:00 - General Checkup
Doctor(ID:102, Name:Dr. John, Specialty:Dermatology)
  Assigned Appointments:
   - 2025-09-12 14:00 - Dermatology Consult
Doctor(ID:103, Name:Dr. Alice, Specialty:Endocrinology)
  Assigned Appointments:
   - 2025-09-15 09:00 - Diabetes Follow-up

--- All Appointments ---
Appointment(2025-09-10 10:00, Reason:General Checkup, Status:completed, Patient:Alice, Doctor:Dr. Smith)
Appointment(2025-09-12 14:00, Reason:Dermatology Consult, Status:canceled, Patient:Bob, Doctor:Dr. John)
Appointment(2025-09-15 09:00, Reason:Diabetes Follow-up, Status:scheduled, Patient:Charlie, Doctor:Dr. Alice)

[Invalid Test] ChronicPatient attempting to schedule too-soon appointment:
ChronicPatient Charlie requires frequent check-ups. Appointment on 2025-09-11 for Too soon follow-up scheduled.
...
ClinicManager destroyed and all objects freed.

📖 Documentation Outline

The full report (PDF) includes:

OOA Analysis (objects, attributes, methods, inheritance).

Class diagram (Patient → ChronicPatient, Doctor, Appointment, ClinicManager).

Code Walkthrough (explanation of design decisions).

Test Demonstration (sample outputs with explanation).

LLM Usage: ChatGPT was used for brainstorming class design, debugging errors (getName() missing), and refining README/documentation.
