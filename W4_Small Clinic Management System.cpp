#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ========================== CLASS PATIENT ==========================
class Patient {
protected:
    string name;                      // tên bệnh nhân
    int id;                           // mã bệnh nhân
    int age;                          // tuổi
    vector<string> medicalHistory;    // lịch sử khám (medical history)
public:
    Patient(string n, int i, int a) : name(n), id(i), age(a) { // constructor
        cout << "Patient " << name << " created" << endl;     // minh họa tạo
    }

    virtual ~Patient() { // destructor ảo để minh họa (yêu cầu của thầy)
        cout << "Patient " << name << " destroyed" << endl;
    }

    // --- Thêm getter getName để các class khác (Appointment, ...) có thể gọi
    string getName() const { return name; }                   // **SỬA LỖI**: thêm getName

    // --- method đặt lịch, có thể override ở lớp con (virtual)
    virtual void scheduleAppointment(const string& date, const string& reason) {
        cout << "Patient " << name << " scheduled appointment on " << date
            << " for " << reason << endl;
    }

    void updateHistory(const string& visit) { medicalHistory.push_back(visit); }

    virtual void displayInfo() const {
        cout << "Patient(ID:" << id << ", Name:" << name << ", Age:" << age << ")" << endl;
        if (!medicalHistory.empty()) {
            cout << "  Medical History:" << endl;
            for (const auto& h : medicalHistory) cout << "   - " << h << endl;
        }
    }
};

// ========================== CLASS CHRONIC PATIENT ==========================
class ChronicPatient : public Patient {
private:
    string conditionType;      // loại bệnh mãn tính
    string lastCheckupDate;    // ngày tái khám gần nhất
public:
    ChronicPatient(string n, int i, int a, string cond, string checkup)
        : Patient(n, i, a), conditionType(cond), lastCheckupDate(checkup) {
        cout << "ChronicPatient " << name << " with condition " << conditionType << " created" << endl;
    }

    ~ChronicPatient() override {
        cout << "ChronicPatient " << name << " destroyed" << endl;
    }

    // override phương thức scheduleAppointment để minh họa behavior khác cho chronic
    void scheduleAppointment(const string& date, const string& reason) override {
        cout << "ChronicPatient " << name
            << " requires frequent check-ups. Appointment on "
            << date << " for " << reason << " scheduled." << endl;
    }

    void displayInfo() const override {
        cout << "ChronicPatient(ID:" << id << ", Name:" << name
            << ", Condition:" << conditionType << ", LastCheckup:" << lastCheckupDate << ")" << endl;
        if (!medicalHistory.empty()) {
            cout << "  Medical History:" << endl;
            for (const auto& h : medicalHistory) cout << "   - " << h << endl;
        }
    }
};

// ========================== CLASS DOCTOR ==========================
class Doctor {
private:
    string name;                        // tên bác sĩ
    int id;                             // mã bác sĩ
    string specialty;                   // chuyên khoa
    vector<string> assignedAppointments; // lưu thông tin đơn giản của appointment (demo)
public:
    Doctor(string n, int i, string s) : name(n), id(i), specialty(s) {
        cout << "Doctor " << name << " created" << endl;
    }

    ~Doctor() {
        cout << "Doctor " << name << " destroyed" << endl;
    }

    // --- Thêm getter để Appointment có thể hiển thị tên bác sĩ
    string getName() const { return name; }                   // **SỬA LỖI**: thêm getName

    void assignAppointment(const string& appInfo) { assignedAppointments.push_back(appInfo); }

    // cập nhật trạng thái appointment theo index (demo)
    void updateAppointmentStatus(int index, const string& status) {
        if (index >= 0 && index < (int)assignedAppointments.size()) {
            assignedAppointments[index] += " [" + status + "]";
        }
    }

    void displayInfo() const {
        cout << "Doctor(ID:" << id << ", Name:" << name << ", Specialty:" << specialty << ")" << endl;
        if (!assignedAppointments.empty()) {
            cout << "  Assigned Appointments:" << endl;
            for (const auto& a : assignedAppointments) cout << "   - " << a << endl;
        }
    }
};

// ========================== CLASS APPOINTMENT ==========================
class Appointment {
private:
    string date;
    string time;
    string reason;
    string status;   // scheduled / completed / canceled
    Patient* patient; // liên kết tới Patient (pointer để minh họa quan hệ)
    Doctor* doctor;   // liên kết tới Doctor
public:
    Appointment(string d, string t, string r, Patient* p, Doctor* doc)
        : date(d), time(t), reason(r), status("scheduled"), patient(p), doctor(doc) {
        // In ra thông tin khi tạo (minh họa)
        cout << "Appointment created for " << (patient ? patient->getName() : string("unknown"))
            << " with Dr. " << (doctor ? doctor->getName() : string("unknown")) << endl;
        // Gán thông tin đơn giản vào doctor để hiển thị (demo)
        if (doctor) doctor->assignAppointment(date + " " + time + " - " + reason);
    }

    ~Appointment() {
        cout << "Appointment on " << date << " " << time << " destroyed" << endl;
    }

    void cancel() {
        status = "canceled";
        cout << "Appointment canceled on " << date << " " << time << endl;
    }

    void complete() {
        status = "completed";
        cout << "Appointment completed on " << date << " " << time << endl;
    }

    void display() const {
        cout << "Appointment(" << date << " " << time << ", Reason:" << reason
            << ", Status:" << status << ", Patient:" << (patient ? patient->getName() : string("unknown"))
            << ", Doctor:" << (doctor ? doctor->getName() : string("unknown")) << ")" << endl;
    }

    string getStatus() const { return status; } // getter status
};

// ========================== CLASS CLINICMANAGER ==========================
class ClinicManager {
private:
    vector<Patient*> patients;
    vector<Doctor*> doctors;
    vector<Appointment*> appointments;
public:
    ClinicManager() = default;

    ~ClinicManager() { // destructor giải phóng bộ nhớ (minh họa)
        for (auto a : appointments) delete a;
        for (auto p : patients) delete p;
        for (auto d : doctors) delete d;
        cout << "ClinicManager destroyed and all objects freed." << endl;
    }

    void addPatient(Patient* p) { patients.push_back(p); }
    void addDoctor(Doctor* d) { doctors.push_back(d); }
    void addAppointment(Appointment* a) { appointments.push_back(a); }

    void showAllPatients() const {
        cout << "--- All Patients ---" << endl;
        for (auto p : patients) p->displayInfo();
    }

    void showAllDoctors() const {
        cout << "--- All Doctors ---" << endl;
        for (auto d : doctors) d->displayInfo();
    }

    void showAllAppointments() const {
        cout << "--- All Appointments ---" << endl;
        for (auto a : appointments) a->display();
    }
};

// ========================== MAIN ==========================
int main() {
    ClinicManager clinic; // lớp quản lý tổng thể (ClinicManager) - đáp ứng yêu cầu

    // --- Tạo 3 bác sĩ ---
    Doctor* d1 = new Doctor("Dr. Smith", 101, "Cardiology");    // created
    Doctor* d2 = new Doctor("Dr. John", 102, "Dermatology");    // created
    Doctor* d3 = new Doctor("Dr. Alice", 103, "Endocrinology"); // created
    clinic.addDoctor(d1); clinic.addDoctor(d2); clinic.addDoctor(d3);

    // --- Tạo 3 bệnh nhân (2 thường + 1 mãn tính) ---
    Patient* p1 = new Patient("Alice", 1, 30);                   // created
    Patient* p2 = new Patient("Bob", 2, 40);                     // created
    ChronicPatient* cp1 = new ChronicPatient("Charlie", 3, 55, "Diabetes", "2025-06-01"); // created
    clinic.addPatient(p1); clinic.addPatient(p2); clinic.addPatient(cp1);

    // --- Thêm medical history ---
    p1->updateHistory("2025-07-01: Flu - Paracetamol");
    p2->updateHistory("2025-08-05: Skin allergy - Antihistamine");
    cp1->updateHistory("2025-06-15: Diabetes check - Insulin");

    // --- Tạo và gán appointment ---
    Appointment* a1 = new Appointment("2025-09-10", "10:00", "General Checkup", p1, d1);
    Appointment* a2 = new Appointment("2025-09-12", "14:00", "Dermatology Consult", p2, d2);
    Appointment* a3 = new Appointment("2025-09-15", "09:00", "Diabetes Follow-up", cp1, d3);
    clinic.addAppointment(a1); clinic.addAppointment(a2); clinic.addAppointment(a3);

    // --- Bệnh nhân lên lịch (gọi method, chronic dùng override) ---
    p1->scheduleAppointment("2025-09-10", "General Checkup");   // normal patient schedule
    p2->scheduleAppointment("2025-09-12", "Dermatology Consult"); // normal patient
    cp1->scheduleAppointment("2025-09-15", "Diabetes Follow-up"); // chronic override

    // --- Cập nhật trạng thái: hoàn thành, hủy ---
    a1->complete();   // mark completed
    a2->cancel();     // mark canceled

    // --- In thông tin hiện trạng ---
    cout << endl;
    clinic.showAllPatients();      // hiển thị danh sách bệnh nhân (và history)
    cout << endl;
    clinic.showAllDoctors();       // hiển thị danh sách bác sĩ (kèm appointments đã assigned)
    cout << endl;
    clinic.showAllAppointments();  // hiển thị chi tiết appointment (status đã updated)
    cout << endl;

    // --- Test case invalid: bệnh nhân mãn tính đặt lịch quá gần (giả lập) ---
    cout << "[Invalid Test] ChronicPatient attempting to schedule too-soon appointment:" << endl;
    cp1->scheduleAppointment("2025-09-11", "Too soon follow-up"); // demo thông báo (bạn có thể thêm validate logic)

    // Khi main returns, ClinicManager destructor sẽ giải phóng tất cả (minh hoạ destructor)
    return 0;
}
