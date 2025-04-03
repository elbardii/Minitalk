#include "minitalk.h"  // الملف اللي فيه تعريف t_client
#include <unistd.h>    // باش نستعملو write

// هاد المتغير العام كيخزن معلومات العميل اللي كيبعث الرسالة
t_client g_client;

// هاد الدالة كتحسب عدد البايتات ديال حرف Unicode
// الغرض: نعرفو واش الحرف عادي (1 بايت) ولا Unicode (2، 3، 4 بايتات)
int count_unicode_bytes(char first_byte)
{
    // إذا كان البايت الأول موجب (0 أو أكثر)، يعني حرف عادي
    if (first_byte >= 0)
        return (1);  // الحرف عادي، غير بايت واحد

    // إذا كان بين -16 و -1، يعني حرف Unicode من 4 بايتات
    else if (first_byte >= -16)
        return (4);

    // إذا كان بين -32 و -17، يعني حرف Unicode من 3 بايتات
    else if (first_byte >= -32)
        return (3);

    // إذا كان أقل من -32، يعني حرف Unicode من 2 بايتات
    return (2);
}

// هاد الدالة كتفحص واش الحرف عادي ولا Unicode
// الغرض: نساعدو الدالة الكبيرة تعرف واش تكتب الحرف مرة وحدة ولا نصبر حتى يكمل
int is_normal_character(char first_byte)
{
    // إذا البايت الأول موجب (0 أو أكثر)، يعني الحرف عادي (مش Unicode)
    if (first_byte >= 0)
        return (1);  // نعم، عادي
    return (0);      // لا، Unicode
}

// هاد الدالة كتكتب الحرف للشاشة
// الغرض: نخرجو الحرف للمستخدم سواء كان عادي أو Unicode
void print_character(char *message, int number_of_bytes)
{
    write(1, message, number_of_bytes);  // نكتبو عدد البايتات المحدد للشاشة (stdout)
}

// هاد الدالة كتعالج عرض الرسالة اللي جات من العميل
// الغرض: نطبعو الحرف سواء كان عادي (1 بايت) أو Unicode (حتى 4 بايتات)
void show_client_message(t_client *client_info)
{
    // نفحصو أول بايت ديال الرسالة
    char first_byte = client_info->message[0];

    // واش الحرف عادي (مش Unicode)؟
    if (is_normal_character(first_byte) == 1)
    {
        // إذا نعم، نطبعو البايت الأول غير مرة وحدة
        print_character(client_info->message, 1);
    }
    else
    {
        // إذا لا، يعني الحرف Unicode، خاصنا نصبر حتى نكملو كل البايتات ديالو

        // نفحصو البايت الحالي، واش هو نهاية بايتات ولا مازال؟
        if (client_info->message[client_info->offset] >= 0)
        {
            // إذا البايت الحالي موجب، يعني كملنا بايتات الحرف السابق
            // نرجعو الموقع للصفر باش نبداو حرف جديد
            client_info->offset = 0;
        }

        // نزيدو الموقع بواحد لأننا تلقينا بايت جديد
        client_info->offset = client_info->offset + 1;

        // نعرفو عدد البايتات الكلي ديال الحرف
        int total_bytes = count_unicode_bytes(first_byte);

        // واش كملنا كل البايتات ديال الحرف؟
        if (client_info->offset == total_bytes)
        {
            // إذا نعم، نطبعو الحرف كامل (كل البايتات)
            print_character(client_info->message, total_bytes);

            // نرجعو الموقع للصفر باش نبداو حرف جديد
            client_info->offset = 0;
        }
    }
}