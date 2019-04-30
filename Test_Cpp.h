#include <string>
#include <any>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace TestNameSpace { class Test3; }
namespace TestNameSpace { class Test4; }
namespace TestNameSpace { class Test5; }


namespace TestNameSpace
{
	class Test1 : public Test2
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [ConfigurationProperty("ABCD", IsDefaultCollection = false)] public Test3 ABCD
		Test3 *getABCD() const;
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [ConfigurationCollection(typeof(Test4), AddItemName = "DEF", CollectionType = ConfigurationElementCollectionType.BasicMap)] public class Test3 : ConfigurationElementCollection
	class Test3 : public ConfigurationElementCollection
	{
	protected:
		ConfigurationElement *CreateNewElement() override;


		std::any GetElementKey(ConfigurationElement *element) override;

	public:
		Test4 *operator [](const std::wstring &Name);

		int IndexOf(Test4 *element);

		void Add(Test4 *element);

	protected:
		void BaseAdd(ConfigurationElement *element) override;

	public:
		void Remove(Test4 *element);

		void RemoveAt(int index);

		void Remove(const std::wstring &name);

		void Clear();
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [ConfigurationCollection(typeof(Test5), AddItemName = "add", CollectionType = ConfigurationElementCollectionType.BasicMap)] public class Test4 : ConfigurationElementCollection
	class Test4 : public ConfigurationElementCollection
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [ConfigurationProperty("name", DefaultValue = "Ga", IsRequired = true, IsKey = true)][StringValidator(InvalidCharacters = " ~!@#$%^&*()[]{}/;'\"|\\", MinLength = 1, MaxLength = 60)] public string Name
		std::wstring getName() const;
		void setName(const std::wstring &value);

		Test4();

		Test4(const std::wstring &elementName);


	protected:
		ConfigurationElement *CreateNewElement() override;


		std::any GetElementKey(ConfigurationElement *element) override;

	public:
		Test5 *operator [](const std::wstring &Name);

		int IndexOf(Test5 *prop);

		void Add(Test5 *prop);

	protected:
		void BaseAdd(ConfigurationElement *element) override;

	public:
		void Remove(Test5 *prop);

		void RemoveAt(int index);

		void Remove(const std::wstring &name);

		void Clear();

	};

	class Test5 : public ConfigurationElement
	{
	public:
		Test5(const std::wstring &key, const std::wstring &value);

		Test5();

		Test5(const std::wstring &elementKey);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [ConfigurationProperty("key", DefaultValue = "Key", IsRequired = true, IsKey = true)] public string Key
		std::wstring getKey() const;
		void setKey(const std::wstring &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [ConfigurationProperty("value", DefaultValue = "Value", IsRequired = true)] public string Value
		std::wstring getValue() const;
		void setValue(const std::wstring &value);
	};
}