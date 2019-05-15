#pragma once

#include "MainPage.g.h"

namespace winrt::GridArtifacts::implementation
{
	using namespace winrt::Windows::Foundation;
	using namespace winrt::Windows::UI::Xaml;

    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        //void ClickHandler(IInspectable const& sender, RoutedEventArgs const& args);
		IAsyncAction OpenBeatFile_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void RefreshDeviceList_Click(IInspectable const& sender, RoutedEventArgs const& e);
	};
}

namespace winrt::GridArtifacts::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
