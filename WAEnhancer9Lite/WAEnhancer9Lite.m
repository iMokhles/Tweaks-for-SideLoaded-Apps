//
//  WAEnhancer9Lite.m
//  WAEnhancer9Lite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import "WAEnhancer9Lite.h"

UISwitch *switchview1;

BOOL GetBool(NSString *key)
{
    return [[[NSUserDefaults standardUserDefaults] objectForKey:key] boolValue];
}

#pragma mark - iPAD Support
hook(UIDevice)
- (BOOL)wa_isDeviceSupported {
    return YES;
}
- (BOOL)wa_shouldBeAskedToReview { // stop asking for review
    return NO;
}
- (BOOL)wa_isDeviceSuspicious {
    return NO;
}
endhook

#pragma mark - jailbreak detection
hook(WASharedAppData)
+ (void)showLocalNotificationForJailbrokenPhoneAndTerminate { // LOL in case any issue ( i don't trust WhatsApp devs ) :P
    return;
}
endhook

#pragma mark - Last Seend

hook(XMPPConnection)
- (void)sendPresenceWithNickname:(id)arg1 {
    if (GetBool(@"lastseen_bool")) {
        return;
    } else {
        return _orig(void, arg1);
    }
}
- (void)sendReadReceiptsForChatMessages:(id)arg1 {
    if (GetBool(@"readmark_bool")) {
        return;
    } else {
        _orig(void, arg1);
    }
}

- (void)sendPlayedReceiptForMessage:(id)arg1 {
    if (GetBool(@"readmark_bool")) {
        return;
    } else {
        _orig(void, arg1);
    }
}
endhook

#pragma mark - WAEnhancer Settings

hook(WAStaticTableViewController)

- (WATableSection *)addSectionAtTop {
    WATableSection *waeTableSection = [[objc_getClass("WATableSection") alloc] init];
    NSMutableArray *sectionsStatic = [self valueForKey:@"_sections"];
    [sectionsStatic insertObject:waeTableSection atIndex:1];
    return waeTableSection;
}
endhook


hook(WASettingsViewController)
- (void)setupTableView {
    
    _orig(void);
    WATableSection *waeTabSection = [(WASettingsViewController *)self addSectionAtTop];
    
    waeTabSection.headerText = @"WAEnhancer9Lite";
    waeTabSection.footerText = @"WhatsApp tweak without jailbreak by ( iMokhles )";
    
    NSString *freezeLastSeen = @"Freeze LastSeen";
    WATableRow *advancedRow = [objc_getClass("WATableRow") new];
    [advancedRow setHandler:^{
        [(WASettingsViewController *)self deselectActiveCell];
        
    }];
    UITableViewCell *freezeLastSeenCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"freezeLastSeenCell"];
    freezeLastSeenCell.selectionStyle = UITableViewCellSelectionStyleNone;
    switchview1 = [UISwitch new];
    [switchview1 setOn:[[[NSUserDefaults standardUserDefaults] objectForKey:@"lastseen_bool"] boolValue] animated:NO];
    switchview1.tag = 8756;
    [switchview1 addTarget:self action:@selector(_didToggleEnableDisable:) forControlEvents:UIControlEventValueChanged];
    freezeLastSeenCell.accessoryView = switchview1;
    [advancedRow setCell:freezeLastSeenCell];
    [freezeLastSeenCell.textLabel setText:freezeLastSeen];
    [freezeLastSeenCell.textLabel setTextAlignment:NSTextAlignmentLeft];
    [waeTabSection addRow:advancedRow];
    
    NSString *disableReadMark = @"Disable ReadMark";
    WATableRow *disableReadMarkRow = [objc_getClass("WATableRow") new];
    [disableReadMarkRow setHandler:^{
        [(WASettingsViewController *)self deselectActiveCell];
        
    }];
    UITableViewCell *disableReadMarkCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"disableReadMarkCell"];
    disableReadMarkCell.selectionStyle = UITableViewCellSelectionStyleNone;
    switchview1 = [UISwitch new];
    [switchview1 setOn:[[[NSUserDefaults standardUserDefaults] objectForKey:@"readmark_bool"] boolValue] animated:NO];
    switchview1.tag = 8757;
    [switchview1 addTarget:self action:@selector(_didToggleEnableDisable:) forControlEvents:UIControlEventValueChanged];
    disableReadMarkCell.accessoryView = switchview1;
    [disableReadMarkRow setCell:disableReadMarkCell];
    [disableReadMarkCell.textLabel setText:disableReadMark];
    [disableReadMarkCell.textLabel setTextAlignment:NSTextAlignmentLeft];
    [waeTabSection addRow:disableReadMarkRow];

}

- (void)_didToggleEnableDisable:(UISwitch *)sw {
    if (sw.tag == 8756) {
        [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:sw.on] forKey:@"lastseen_bool"];
    } else if (sw.tag == 8757) {
        [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:sw.on] forKey:@"readmark_bool"];
    }
    [[NSUserDefaults standardUserDefaults] synchronize];
}

endhook