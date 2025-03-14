# Minitalk
### تحليل شامل للمشروع "Minitalk"

#### 1. **نظرة عامة على المشروع**
مشروع "Minitalk" هو برنامج بسيط مكتوب بلغة البرمجة C يهدف إلى إنشاء نظام تواصل بين عمليتين (processes) باستخدام الإشارات (signals) في أنظمة التشغيل المستندة إلى UNIX. الهدف الأساسي من المشروع هو محاكاة آلية اتصال بسيطة بين خادوم (server) وعميل (client)، حيث يقوم العميل بإرسال رسالة نصية إلى الخادوم باستخدام إشارتي `SIGUSR1` و`SIGUSR2` لتمثيل البتات (0 و1)، والخادوم يستقبل هذه الإشارات ويعيد بناء الرسالة لعرضها على الشاشة. 

المشكل الذي يعالجه المشروع هو كيفية نقل البيانات بين عمليتين دون استخدام آليات التواصل التقليدية مثل الأنابيب (pipes) أو الملفات المشتركة، مما يجعله تمرينًا تعليميًا ممتازًا لفهم إدارة الإشارات في أنظمة التشغيل. الميزات الرئيسية تشمل:
- إرسال رسائل نصية باستخدام الإشارات.
- دعم الرسائل بأحرف ASCII وUnicode.
- معالجة الأخطاء مثل أرقام PID غير صالحة أو انقطاع الاتصال.

#### 2. **هيكلة الملفات**
المشروع يتكون من مجموعة من ملفات C التي تعمل معًا لتحقيق الهدف. فيما يلي قائمة بالملفات ودورها:
- **`client.c`**: يحتوي على الكود الرئيسي للعميل، الذي يأخذ رقم PID الخاص بالخادوم والرسالة كمعطيات ويبدأ عملية الإرسال.
- **`server.c`**: يحتوي على الكود الرئيسي للخادوم، الذي يعرض رقم PID الخاص به ويستمع للإشارات لاستقبال الرسائل.
- **`ft_upload.c`**: يحتوي على منطق إرسال الرسالة من العميل إلى الخادوم باستخدام الإشارات.
- **`ft_put_client_message.c`**: يدير عرض الرسائل المستقبلة على الخادوم، مع دعم أحرف Unicode.
- **`ft_putstr_fd.c`**: دالة مساعدة لكتابة سلسلة نصية إلى ملف محدد (مثل stdout أو stderr).
- **`ft_loadpid.c`**: دالة لتحويل سلسلة نصية إلى رقم PID صالح.
- **`ft_putpid_fd.c`**: دالة لطباعة رقم PID على ملف محدد.
- **`ft_strlen.c`**: دالة لحساب طول السلسلة النصية (بطريقة تكرارية).
- **`ft_putchar_fd.c`**: دالة لكتابة حرف واحد إلى ملف محدد.
- **`ft_reset_client.c`**: دالة لإعادة تعيين حالة العميل على الخادوم.
- **`minitalk.h`**: ملف رأس (header) يحتوي على تعريفات الهياكل (structs) مثل `t_server` و`t_client`، بالإضافة إلى تضمين المكتبات اللازمة.

#### 3. **تحليل الكود**
##### **`client.c`**
- **الدور**: نقطة البداية للعميل.
- **تحليل سطر بسطر**:
  - `if (argc != 3)`: التحقق من أن عدد الوسائط هو 3 (اسم البرنامج، PID، والرسالة).
  - `server_pid = ft_loadpid(argv[1])`: تحويل PID من سلسلة إلى عدد صحيح.
  - `if (server_pid == 0)`: التحقق من صلاحية PID، وإذا كان غير صالح يتم طباعة رسالة خطأ.
  - `ft_upload(server_pid, argv[2])`: بدء عملية إرسال الرسالة إلى الخادوم.
- **النمط المعماري**: تصميم بسيط مع التركيز على معالجة الأخطاء الأساسية.

##### **`ft_upload.c`**
- **الدور**: إرسال الرسالة بت ببت باستخدام الإشارات.
- **الدوال الرئيسية**:
  - `ft_server_reset`: تهيئة متغيرات العميل (مثل PID، الرسالة، ومؤشر البت).
  - `ft_send_bit`: إرسال بت واحد باستخدام `SIGUSR1` (0) أو `SIGUSR2` (1).
  - `ft_send`: معالج الإشارات الذي يدير تقدم إرسال الرسالة بناءً على رد الخادوم.
  - `ft_client_error`: معالجة الأخطاء مثل انقطاع الاتصال.
- **النمط**: استخدام نهج قائم على الإشارات مع حلقة انتظار رد الخادوم.

##### **`server.c`**
- **الدور**: استقبال الإشارات وإعادة بناء الرسالة.
- **تحليل**:
  - `ft_putpid_fd(getpid(), 1)`: عرض PID الخادوم.
  - `sigaction(SIGUSR1, &sa, NULL)`: تسجيل معالج الإشارات `ft_receive`.
  - `ft_receive`: يستقبل الإشارات، يجمع البتات، ويعرض الحروف عند اكتمال 8 بتات.
- **النمط**: تصميم قائم على الحدث (event-driven) باستخدام `sigaction`.

##### **الدوال المساعدة**
- **`ft_put_client_message.c`**: يدير عرض الأحرف مع دعم Unicode باستخدام تحليل طول التسلسل.
- **`ft_strlen.c`**: تكرارية لحساب طول السلسلة، وهي أقل كفاءة من التنفيذ التقليدي ولكنها تعليمية.
- **`ft_loadpid.c`**: تحقق صارم من صلاحية PID (حد أقصى 6 أرقام).

#### 4. **التبعيات (Dependencies)**
- **`signal.h`**: لإدارة الإشارات (`SIGUSR1`, `SIGUSR2`, `sigaction`).
- **`unistd.h`**: لوظائف مثل `write`، `usleep`، و`getpid`.
- لا توجد مكتبات خارجية إضافية، مما يجعل المشروع خفيفًا ومستقلًا.

#### 5. **طريقة الاستعمال**
1. **الإعداد**:
   - قم بتجميع المشروع باستخدام `gcc`:
     ```bash
     gcc -o server server.c ft_putstr_fd.c ft_putpid_fd.c ft_putchar_fd.c ft_reset_client.c ft_put_client_message.c
     gcc -o client client.c ft_upload.c ft_putstr_fd.c ft_loadpid.c ft_putchar_fd.c ft_strlen.c
     ```
2. **التشغيل**:
   - شغل الخادوم أولاً: `./server` (سيظهر PID).
   - شغل العميل مع PID الخادوم والرسالة: `./client <PID> "Hello World"`.
3. **ملاحظات**: لا يحتاج إلى إعدادات خاصة، لكن يجب أن يكون النظام يدعم الإشارات.

#### 7. **الخلاصة**
مشروع "Minitalk" يحقق هدفه كأداة تعليمية لفهم الإشارات في UNIX، مع تصميم بسيط وواضح. **نقاط القوة** تشمل بساطته، دعم Unicode، ومعالجة الأخطاء الأساسية. **نقاط الضعف** تتضمن الأداء المنخفض لبعض الدوال (مثل `ft_strlen`) وقلة المرونة في التعامل مع السيناريوهات المعقدة. بشكل عام، هو مشروع ناجح لأغراض التعلم مع مجال للتحسين في التطبيقات العملية.