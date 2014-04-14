/*
 * Copyright 2014 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Martin Preisler <mpreisle@redhat.com>
 */

#include "APIHelpers.h"
#include <QObject>

extern "C"
{
#include <oscap_error.h>
#include <xccdf_policy.h>
}

QString oscapTextIteratorGetPreferred(struct oscap_text_iterator* it, const QString& lang)
{
    char* preferred_s = oscap_textlist_get_preferred_plaintext(it, lang.isEmpty() ? NULL : lang.toUtf8().constData());
    oscap_text_iterator_free(it);
    const QString ret(preferred_s != NULL ? QString::fromUtf8(preferred_s) : QObject::tr("(none)"));
    free(preferred_s);

    return ret;
}

QString oscapItemGetReadableTitle(struct xccdf_item *item, struct xccdf_policy *policy, const QString& lang)
{
    char* readable_s = xccdf_policy_get_readable_item_title(policy, item, lang.isEmpty() ? NULL : lang.toUtf8().constData());
    const QString ret(readable_s != NULL ? QString::fromUtf8(readable_s) : QObject::tr("(none)"));
    free(readable_s);
    return ret;
}

QString oscapItemGetReadableDescription(struct xccdf_item *item, struct xccdf_policy *policy, const QString& lang)
{
    char* readable_s = xccdf_policy_get_readable_item_description(policy, item, lang.isEmpty() ? NULL : lang.toUtf8().constData());
    const QString ret(readable_s != NULL ? QString::fromUtf8(readable_s) : QObject::tr("(none)"));
    free(readable_s);
    return ret;
}

QString oscapErrDesc()
{
    return QString::fromUtf8(oscap_err_desc());
}
